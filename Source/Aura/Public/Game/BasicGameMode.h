

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BasicGameMode.generated.h"

class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class AURA_API ABasicGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character class defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};

