

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class AURA_API AGameProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameProjectile();

	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
};
