


#include "Character/EnemyCharacter.h"

#include "GameplayTagsHolder.h"
#include "AbilitySystem/AbilitySystemComponentBase.h"
#include "AbilitySystem/AbilitySystemLibrary.h"
#include "AbilitySystem/AttributeSetBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/BaseUserWidget.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentBase>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

#pragma region Interfaces Implementation
#pragma region Enemy interface
void AEnemyCharacter::HightlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponMesh->SetRenderCustomDepth(true);
}

void AEnemyCharacter::UnHightlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
#pragma endregion

#pragma region Combat interface
int32 AEnemyCharacter::GetCharacterLevel()
{
	return Level;
}
#pragma endregion
#pragma endregion

void AEnemyCharacter::InitializeDefaultsAttributes() const
{
	UAbilitySystemLibrary::InitializeDefaultAttributes(this, GetAbilitySystemComponent(), CharacterClass, Level);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (const auto Widget = Cast<UBaseUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		Widget->SetWidgetController(this);
	}

	if (const auto AS = CastChecked<UAttributeSetBase>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

		BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

		UAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass, Level);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTagsHolder::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AEnemyCharacter::HitReactTagChanged);
		OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
		OnHealthChanged.Broadcast(AS->GetHealth());
	}
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	if (auto ASCB = Cast<UAbilitySystemComponentBase>(AbilitySystemComponent))
	{
		ASCB->AbilityActorInfoSet();
		InitializeDefaultsAttributes();
	}
}

#pragma region Damage Handling

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AEnemyCharacter::Die()
{
	SetLifeSpan(5.0f);
	Super::Die();
}
#pragma endregion