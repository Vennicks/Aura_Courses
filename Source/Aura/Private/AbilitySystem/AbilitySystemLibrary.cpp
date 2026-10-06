


#include "AbilitySystem/AbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Editor/Kismet/Internal/Blueprints/BlueprintDependencies.h"
#include "Game/BasicGameMode.h"
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

void UAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass, float Level)
{
	
	if (auto GM = Cast<ABasicGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		auto ClassInfo = GM->CharacterClassInfo;
		FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

		auto context = ASC->MakeEffectContext();
		context.AddSourceObject(ASC->GetAvatarActor());

		const auto PrimarySpec = ASC->MakeOutgoingSpec(ClassDefaultInfo.GEPrimaryAttributes, Level, context);
		const auto SecondarySpec = ASC->MakeOutgoingSpec(ClassInfo->GESecondAttributes, Level, context);
		const auto VitalSpec = ASC->MakeOutgoingSpec(ClassInfo->GEVitalAttributes, Level, context);

		ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpec.Data.Get());
		ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpec.Data.Get());
		ASC->ApplyGameplayEffectSpecToSelf(*VitalSpec.Data.Get());
	}
}

void UAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass, float Level)
{

	if (auto GM = Cast<ABasicGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		for (auto Ability : GM->CharacterClassInfo->CommonAbilities)
		{
			ASC->GiveAbility(FGameplayAbilitySpec(Ability, Level));
		}
	}
}

UCharacterClassInfo* UAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	if (auto GM = Cast<ABasicGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return GM->CharacterClassInfo;
	}
	return nullptr;
}
