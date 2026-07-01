

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

protected:
	/** Begin Enemy interface **/
	virtual void HightlightActor() override;
	virtual void UnHightlightActor() override;
	/** End Enemy interface **/

	virtual void BeginPlay() override;
};
