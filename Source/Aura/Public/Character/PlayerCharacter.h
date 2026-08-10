

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:

#pragma region Combat interface
	virtual int32 GetCharacterLevel() override;
#pragma endregion

	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;
};
