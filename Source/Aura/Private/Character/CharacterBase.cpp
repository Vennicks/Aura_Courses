


#include "Character/CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilitySystemComponentBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::BeginPlay()
{ 
	Super::BeginPlay();
	
}

void ACharacterBase::InitAbilityActorInfo()
{
}

FVector ACharacterBase::GetCombatSocketLocation()
{
	return WeaponMesh->GetSocketLocation(WeaponTipSocket);
}

void ACharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const
{
	check(GetAbilitySystemComponent());
	check(GameplayEffect);
	auto Context = GetAbilitySystemComponent()->MakeEffectContext();
	Context.AddSourceObject(this);
	auto Spec = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, Level, Context);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), GetAbilitySystemComponent());
}

void ACharacterBase::InitializeDefaultsAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1);
	ApplyEffectToSelf(DefaultVitalAttributes, 1);
}

void ACharacterBase::InitializeAbilities() const
{
	if (!HasAuthority())
		return;

	UAbilitySystemComponentBase* ASC = CastChecked<UAbilitySystemComponentBase>(GetAbilitySystemComponent());
	ASC->AddAbilities(StartupAbilities);
}
