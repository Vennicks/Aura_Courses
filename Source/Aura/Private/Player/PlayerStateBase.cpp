


#include "Player/PlayerStateBase.h"

#include "AbilitySystem/AbilitySystemComponentBase.h"
#include "AbilitySystem/AttributeSetBase.h"

APlayerStateBase::APlayerStateBase()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentBase>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>("AttributeSet");
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
