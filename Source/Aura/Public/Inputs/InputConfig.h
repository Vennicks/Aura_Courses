

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "InputConfig.generated.h"


USTRUCT(BlueprintType)
struct FLinkInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class AURA_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* GetInputActionTag(FGameplayTag& InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<FLinkInputAction> InputActions;
};
