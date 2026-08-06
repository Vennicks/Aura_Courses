


#include "AbilitySystem/AbilitySystemComponentBase.h"

void UAbilitySystemComponentBase::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAbilitySystemComponentBase::OnEffectApplied);


}

void UAbilitySystemComponentBase::OnEffectApplied(UAbilitySystemComponent* AbilitySystem,
                                                  const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);

	OnEffectAppliedDelegate.Broadcast(AssetTags);
}
