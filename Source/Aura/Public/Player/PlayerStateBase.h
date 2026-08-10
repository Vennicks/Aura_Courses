

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS(BlueprintType)
class AURA_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	APlayerStateBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	int32 GetCharacterLevel() const { return Level; }

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing  = OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

};
