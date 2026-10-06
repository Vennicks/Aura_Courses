

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "CharacterBase.generated.h"

class UGameplayAbility;
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

	UPROPERTY(EditAnywhere, Category=Combat)
	FName WeaponTipSocket;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	void Dissolve();



	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	virtual FVector GetCombatSocketLocation() override;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;

	virtual void InitializeDefaultsAttributes() const;

	void InitializeAbilities() const;

private:
	UPROPERTY(EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
#pragma region Combat
public:
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
protected:
	virtual void Die() override;

private:
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* HitReactMontage = nullptr;

	UFUNCTION(Reliable, NetMulticast)
	virtual void MulticastHandleDeath();
#pragma endregion

};
