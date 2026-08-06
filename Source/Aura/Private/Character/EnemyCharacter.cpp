


#include "Character/EnemyCharacter.h"

#include "AbilitySystem/AbilitySystemComponentBase.h"
#include "AbilitySystem/AttributeSetBase.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentBase>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>("AttributeSet");
}

void AEnemyCharacter::HightlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponMesh->SetRenderCustomDepth(true);
}

void AEnemyCharacter::UnHightlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	if (auto ASCB = Cast<UAbilitySystemComponentBase>(AbilitySystemComponent))
	{
		ASCB->AbilityActorInfoSet();
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to cast AbilitySystemComponent to UAbilitySystemComponentBase"));
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to cast AbilitySystemComponent to UAbilitySystemComponentBase"));
		}
	}
}
