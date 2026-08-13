


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "GameplayTagsHolder.h"
#include "AbilitySystem/AttributeSetBase.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAttributeSetBase* AS = CastChecked<UAttributeSetBase>(AttributeSet);
	for (auto &pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value()).AddLambda([this, pair, AS](const FOnAttributeChangeData& Data)
		{
				BroadcastAttributeInfo(pair.Key, pair.Value());
		});
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	auto AS = CastChecked<UAttributeSetBase>(AttributeSet);
	check(AttributeInfo);

	for (auto& pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(pair.Key, pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag, const FGameplayAttribute& Attribute) const
{
	auto Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	OnAttributeChanged.Broadcast(Info);
}
