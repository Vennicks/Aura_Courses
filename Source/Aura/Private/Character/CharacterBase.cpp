


#include "Character/CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilitySystemComponentBase.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		auto DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		auto WeaponDynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		WeaponMesh->SetMaterial(0, WeaponDynamicMatInst);
		StartWeaponDissolveTimeline(WeaponDynamicMatInst);
	}
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

UAnimMontage* ACharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ACharacterBase::MulticastHandleDeath_Implementation()
{
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}	

void ACharacterBase::Die()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	MulticastHandleDeath();
}