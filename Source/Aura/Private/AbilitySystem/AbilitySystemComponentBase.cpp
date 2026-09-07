


#include "AbilitySystem/AbilitySystemComponentBase.h"

#include "GameplayTagsHolder.h"
#include "GameplayTagsHolder.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

void UAbilitySystemComponentBase::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAbilitySystemComponentBase::Client_OnEffectApplied);
}

void UAbilitySystemComponentBase::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAdd)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : AbilitiesToAdd)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this);
		if (const auto CastAbility = Cast<UBaseGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(CastAbility->StartupGameplayTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAbilitySystemComponentBase::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
		return;
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAbilitySystemComponentBase::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
		return;
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UAbilitySystemComponentBase::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
}

void UAbilitySystemComponentBase::Client_OnEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystem,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);

	OnEffectAppliedDelegate.Broadcast(AssetTags);
}
