

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

USTRUCT(BlueprintType)
struct FEffectDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::DoNotRemove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;
};

UCLASS()
class AURA_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectActor();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	TArray<FEffectDefinition> EffectDefinitions;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	float ActorLevel = 1.f;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> AppliedEffects;
	void ApplyEffect(AActor* TargetActor, FEffectDefinition GameplayEffectClass);

};
