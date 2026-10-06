

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "ProjectileSpell.generated.h"

class AGameProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UProjectileSpell : public UBaseGameplayAbility
{
	GENERATED_BODY()
protected:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AGameProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffect;

};
