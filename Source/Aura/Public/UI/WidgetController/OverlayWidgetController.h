

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/WidgetController/UserWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChangedSignature, float, NewStat);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UUserWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnStatChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnStatChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnStatChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnStatChangedSignature OnMaxManaChanged;

protected:
	void OnHealthChangedInternal(const FOnAttributeChangeData& Data);
	void OnMaxHealthChangedInternal(const FOnAttributeChangeData& Data);
	void OnManaChangedInternal(const FOnAttributeChangeData& Data);
	void OnMaxManaChangedInternal(const FOnAttributeChangeData& Data);
};
