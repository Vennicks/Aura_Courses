


#include "Actor/EffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AttributeSetBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AEffectActor::AEffectActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
}

void AEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		auto AttributeSet = Cast <UAttributeSetBase>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAttributeSetBase::StaticClass()));
		
		auto UnConstAS = const_cast<UAttributeSetBase*>(AttributeSet);
		UnConstAS->SetHealth(AttributeSet->GetHealth() + 10.f);
		UnConstAS->SetMana(AttributeSet->GetMana() - 10.f);
		Destroy();
	}
}

void AEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
}

void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::EndOverlap);
}

