

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/WidgetController/UserWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
class UBaseUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRowBase : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag InfoTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText InfoMessage = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBaseUserWidget> InfoWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* InfoImage = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChangedSignature, float, NewStat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfoWidgetRowSignature, FUIWidgetRowBase, Signature);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UUserWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnStatChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnStatChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnStatChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnStatChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Infos")
	FOnInfoWidgetRowSignature OnInfoWidgetRowChanged;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> InfoWidgetDataTable = nullptr;
};