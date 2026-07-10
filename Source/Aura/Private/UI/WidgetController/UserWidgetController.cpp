


#include "UI/WidgetController/UserWidgetController.h"

void UUserWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UUserWidgetController::BroadcastInitialValues()
{
}

void UUserWidgetController::BindCallbacksToDependencies()
{
}
