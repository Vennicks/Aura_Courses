

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "CharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet *GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(EditAnywhere, Category=Combat)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Attributes)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Attributes)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes = nullptr;;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Attributes)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes = nullptr;

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;

	void InitializeDefaultsAttributes() const;
};
