


#include "AbilitySystem/Abilities/ProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsHolder.h"
#include "AbilitySystem/AbilitySystemLibrary.h"
#include "Actor/GameProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		AActor* Owner = GetAvatarActorFromActorInfo();
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Owner))
		{
			FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			auto Rotation = (TargetLocation - SocketLocation).Rotation();
			FTransform SpawnTransform;

			Rotation.Pitch = 0.f;
			SpawnTransform.SetLocation(SocketLocation);
			SpawnTransform.SetRotation(Rotation.Quaternion());

			//Set projectile rotation to the forward vector of the character

			auto ProjectileInstance = GetWorld()->SpawnActorDeferred<AGameProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetAvatarActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			auto SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
			auto SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffect, GetAbilityLevel(), SourceASC->MakeEffectContext());
			
			
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FGameplayTagsHolder::Get().Damage, Damage.GetValueAtLevel(GetAbilityLevel()));

			ProjectileInstance->DamageEffectSpecHandle = SpecHandle;
			ProjectileInstance->FinishSpawning(SpawnTransform);
		}
	}
}

void UProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
