


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AbilitySystemComponentBase.h"
#include "AbilitySystem/AttributeSetBase.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const auto ASB = CastChecked<UAttributeSetBase>(AttributeSet);
	OnHealthChanged.Broadcast(ASB->GetHealth());
	OnMaxHealthChanged.Broadcast(ASB->GetMaxHealth());
	OnManaChanged.Broadcast(ASB->GetMana());
	OnMaxManaChanged.Broadcast(ASB->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const auto ASB = CastChecked<UAttributeSetBase>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASB->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASB->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASB->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASB->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	});

	Cast<UAbilitySystemComponentBase>(AbilitySystemComponent)->OnEffectAppliedDelegate.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			if (IsValid(InfoWidgetDataTable))
			{
				const FUIWidgetRowBase* Row = InfoWidgetDataTable->FindRow<FUIWidgetRowBase>(Tag.GetTagName(), TEXT(""));
				if (Row)
				{
					OnInfoWidgetRowChanged.Broadcast(*Row);
				} else
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Info widget row not found for tag: ") + Tag.GetTagName().ToString());
					} else
					{
						UE_LOG(LogTemp, Error, TEXT("Info widget row not found for tag: %s"), *Tag.GetTagName().ToString());
					}
				}
			}
		}
	});
}