

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/HUD/BaseHUD.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetControllerWidgetController;

/**
 * 
 */

UCLASS()
class AURA_API UAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure)
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
