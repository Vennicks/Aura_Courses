

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "PlayerControllerBase.generated.h"
/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

UCLASS()
class AURA_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerControllerBase();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputContext = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction = nullptr;

	void Move(const struct FInputActionValue& Value);
	void CursorTrace();

	TScriptInterface<IEnemyInterface> SelectedActor = nullptr;
};
