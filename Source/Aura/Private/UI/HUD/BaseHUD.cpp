


#include "UI/HUD/BaseHUD.h"

#include "UI/Widget/BaseUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ABaseHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void ABaseHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay class uninitialized"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialized"));

	const FWidgetControllerParams WCParams(PC, PS, ASC, AS);

	OverlayWidget = CreateWidget<UBaseUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidgetController = GetOverlayWidgetController(WCParams);

	OverlayWidget->SetWidgetController(OverlayWidgetController);

	OverlayWidgetController->BroadcastInitialValues();

	OverlayWidget->AddToViewport();
}