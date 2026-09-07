

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "PlayerControllerBase.generated.h"
class USplineComponent;
class UAbilitySystemComponentBase;
struct FGameplayTag;
class UInputConfig;
/**
 * 
 */
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

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputConfig> InputConfig = nullptr;


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

	void CursorTrace();
	FHitResult CursorHit;

	TScriptInterface<IEnemyInterface> SelectedActor = nullptr;
};
