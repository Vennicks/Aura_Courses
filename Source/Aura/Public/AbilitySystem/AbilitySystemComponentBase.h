

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

protected:
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystem, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
