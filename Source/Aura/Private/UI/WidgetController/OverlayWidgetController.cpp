


#include "UI/WidgetController/OverlayWidgetController.h"

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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ASB->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnHealthChangedInternal);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ASB->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxHealthChangedInternal);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ASB->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnManaChangedInternal);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ASB->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxManaChangedInternal);
}

void UOverlayWidgetController::OnHealthChangedInternal(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxHealthChangedInternal(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnManaChangedInternal(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxManaChangedInternal(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
