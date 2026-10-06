

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AttributeSetBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

enum class ECharacterClass : uint8;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	
#pragma region Interfaces Implementation
#pragma region Enemy interface
	virtual void HightlightActor() override;
	virtual void UnHightlightActor() override;
#pragma endregion

#pragma region Combat interface
	virtual int32 GetCharacterLevel() override;
#pragma endregion
#pragma endregion

#pragma region EnemyInfoWidget interface
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintAssignable)
	FOnStatChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnStatChangedSignature OnMaxHealthChanged;

#pragma endregion

#pragma region DamageHandling
public:
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	void HitReactTagChanged(const FGameplayTag Tag, int32 NewCount);

	virtual void Die() override;
private:
	float BaseWalkSpeed = 0;
#pragma endregion

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	virtual void InitializeDefaultsAttributes() const override;
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
