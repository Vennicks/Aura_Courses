


#include "Player/PlayerControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagsHolder.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AbilitySystemComponentBase.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Inputs/GameInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widget/DamageTextComponent.h"

#pragma region Defaults
APlayerControllerBase::APlayerControllerBase()
{
	bReplicates = true;
	AutoRunSpline = CreateDefaultSubobject<USplineComponent>(TEXT("AutoRunSpline"));
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	check(InputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false); 
	SetInputMode(InputMode);
}

void APlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

UAbilitySystemComponentBase* APlayerControllerBase::GetASC()
{
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponentBase>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return AbilitySystemComponent;
}
#pragma endregion

#pragma region Input Bindings
void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	UGameInputComponent* GameInputComponent = CastChecked<UGameInputComponent>(InputComponent);
	GameInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Move);
	GameInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &APlayerControllerBase::ShiftPressed);
	GameInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &APlayerControllerBase::ShiftReleased);
	GameInputComponent->BindAction(ShiftAction, ETriggerEvent::Canceled, this, &APlayerControllerBase::ShiftReleased);
	
	GameInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void APlayerControllerBase::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FGameplayTagsHolder::Get().InputTag_LMB))
	{
		bTargeting = SelectedActor ? true : false;
		bAutoRunning = false;
	}
}

void APlayerControllerBase::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FGameplayTagsHolder::Get().InputTag_LMB) || bTargeting || bShiftKeyDown)
	{
		if (!GetASC())
			return;
		GetASC()->AbilityInputTagReleased(InputTag);
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				AutoRunSpline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					AutoRunSpline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					//DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Red, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints.Last();
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void APlayerControllerBase::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FGameplayTagsHolder::Get().InputTag_LMB) || bTargeting || bShiftKeyDown)
	{
		if (!GetASC())
			return;
		GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	
	FollowTime += GetWorld()->GetDeltaSeconds();
	if (CursorHit.bBlockingHit)
	{
		CachedDestination = CursorHit.ImpactPoint;
		//DrawDebugSphere(GetWorld(), CachedDestination, 10.0f, 12, FColor::Green, false, 5.0f);
	}
	if (auto ControlledPawn = GetPawn())
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0f);
	}
}
#pragma endregion

#pragma region Move Handling

void APlayerControllerBase::Move(const struct FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator YawRotation(0, GetControlRotation().Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (auto ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerControllerBase::AutoRun()
{
	if (bAutoRunning)
	{
		if (auto ControlledPawn = GetPawn())
		{
			const FVector LocationOnSpline = AutoRunSpline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
			const FVector Direction = AutoRunSpline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
			ControlledPawn->AddMovementInput(Direction, 1.0f);

			const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
			if (DistanceToDestination <= AutoRunAcceptanceRadius)
			{
				bAutoRunning = false;
			}
		}
	}
}

#pragma endregion

#pragma region Cursor Trace
void APlayerControllerBase::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	if (SelectedActor)
		SelectedActor->UnHightlightActor();

	SelectedActor = CursorHit.GetActor();

	if (SelectedActor)
		SelectedActor->HightlightActor();

}
#pragma endregion

void APlayerControllerBase::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* Target)
{
	if (IsValid(Target) && DamageTextComponentClass)
	{
		auto DamageText = NewObject<UDamageTextComponent>(Target, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(Target->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}
