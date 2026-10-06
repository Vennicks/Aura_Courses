

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "PlayerControllerBase.generated.h"

class UDamageTextComponent;
class USplineComponent;
class UAbilitySystemComponentBase;
struct FGameplayTag;
class UInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UBaseGameplayAbility;

UCLASS()
class AURA_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
#pragma region Defaults
public:
	APlayerControllerBase();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	UAbilitySystemComponentBase* GetASC();

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponentBase> AbilitySystemComponent = nullptr;
#pragma endregion

#pragma region Inputs Handling
protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputContext = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ShiftAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputConfig> InputConfig = nullptr;

	void ShiftPressed(){bShiftKeyDown = true;}
	void ShiftReleased(){bShiftKeyDown = false;}
	bool bShiftKeyDown = false;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

#pragma endregion

#pragma region Move handling
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> AutoRunSpline = nullptr;

	FVector CachedDestination = FVector::ZeroVector;
	float  FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	float AutoRunAcceptanceRadius = 50.f;
	bool bTargeting = false;
private:
	void Move(const struct FInputActionValue& Value);
	void AutoRun();
#pragma endregion

#pragma region Cursor Trace
	void CursorTrace();
	FHitResult CursorHit;

	TScriptInterface<IEnemyInterface> SelectedActor = nullptr;
#pragma endregion
public:
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* Target);
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
