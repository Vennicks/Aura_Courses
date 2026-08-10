

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	
#pragma region Interfaces Implementation
#pragma region Enemy interface
	virtual void HightlightActor() override;
	virtual void UnHightlightActor() override;
#pragma endregion

#pragma region Combat interface
	virtual int32 GetCharacterLevel() override;
#pragma endregion
#pragma endregion

protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;
};
