


#include "GameAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "GameplayTagsHolder.h"

UGameAssetManager& UGameAssetManager::Get()
{
	check(GEngine)
	auto AssetManager = Cast<UGameAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UGameAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FGameplayTagsHolder::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
