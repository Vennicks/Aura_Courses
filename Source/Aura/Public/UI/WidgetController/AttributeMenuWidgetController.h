

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UserWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;
class UAttributeInfo;
struct FAttributeInfoStruct;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChangedSignature, const FAttributeInfoStruct&, Info);


UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UUserWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedSignature OnAttributeChanged;

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

protected:
	void BroadcastAttributeInfo(const FGameplayTag& Tag, const FGameplayAttribute& Attribute) const;
};
