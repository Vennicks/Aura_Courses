

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemComponentBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectApplied, const FGameplayTagContainer&);

UCLASS()
class AURA_API UAbilitySystemComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	FOnEffectApplied OnEffectAppliedDelegate;

	void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAdd);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
protected:
	UFUNCTION(Client, Reliable)
	void Client_OnEffectApplied(UAbilitySystemComponent* AbilitySystem, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
