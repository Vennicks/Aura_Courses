


#include "Actor/EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AttributeSetBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AEffectActor::AEffectActor()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

}


void AEffectActor::ApplyEffect(AActor* TargetActor, FEffectDefinition Effect)
{
	if (auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		check(Effect.GameplayEffectClass);
		auto EffectContext = TargetASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		auto EffectSpecHandle = TargetASC->MakeOutgoingSpec(Effect.GameplayEffectClass, ActorLevel, EffectContext);

		auto EffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		if (Effect.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			AppliedEffects.Add(EffectHandle, TargetASC);
		}
	}
}

void AEffectActor::OnOverlap(AActor* TargetActor)
{
	for (auto Effect : EffectDefinitions)
	{
		if (Effect.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffect(TargetActor, Effect);
		}
	}
}

void AEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (auto Effect : EffectDefinitions)
	{
		if (Effect.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffect(TargetActor, Effect);
		}

		if (Effect.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			if (auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
			{
				TArray<FActiveGameplayEffectHandle> EffectsToRemove;
				for (auto& AppliedEffect : AppliedEffects)
				{
					if (AppliedEffect.Value == TargetASC && AppliedEffect.Key.IsValid())
					{
						TargetASC->RemoveActiveGameplayEffect(AppliedEffect.Key);
						EffectsToRemove.Add(AppliedEffect.Key);
					}
				}
				for (auto& EffectHandle : EffectsToRemove)
				{
					AppliedEffects.FindAndRemoveChecked(EffectHandle);
				}
			}
		}
	}
}

void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

