


#include "AbilitySystem/Abilities/ProjectileSpell.h"

#include "Actor/GameProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (HasAuthority(&ActivationInfo))
	{
		AActor* Owner = GetAvatarActorFromActorInfo();
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Owner))
		{
			FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SocketLocation);

			//Set projectile rotation to the forward vector of the character

			auto ProjectileInstance = GetWorld()->SpawnActorDeferred<AGameProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetAvatarActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			ProjectileInstance->FinishSpawning(SpawnTransform);
		}
	}
}
