


#include "AbilitySystem/AbilitySystemLibrary.h"

#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerStateBase.h"
#include "UI/HUD/BaseHUD.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/UserWidgetController.h"

UOverlayWidgetController* UAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (auto hud = Cast<ABaseHUD>(PC->GetHUD()))
		{
			auto PS = PC->GetPlayerState<APlayerStateBase>();
			auto ASC = PS ? PS->GetAbilitySystemComponent() : nullptr;
			auto AS = PS->GetAttributeSet();
			const FWidgetControllerParams Params(PC, PS, ASC, AS);
			return hud->GetOverlayWidgetController(Params);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (auto hud = Cast<ABaseHUD>(PC->GetHUD()))
		{
			auto PS = PC->GetPlayerState<APlayerStateBase>();
			auto ASC = PS ? PS->GetAbilitySystemComponent() : nullptr;
			auto AS = PS->GetAttributeSet();
			const FWidgetControllerParams Params(PC, PS, ASC, AS);
			return hud->GetAttributeMenuWidgetController(Params);
		}
	}
	return nullptr;
}
