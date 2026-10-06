

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	None UMETA(DisplayName = "None"),
	Warrior UMETA(DisplayName = "Warrior"),
	Elementalist UMETA(DisplayName = "Elementalist"),
	Rogue UMETA(DisplayName = "Rogue"),
	Cleric UMETA(DisplayName = "Cleric"),
	Paladin UMETA(DisplayName = "Paladin"),
	Ranger UMETA(DisplayName = "Ranger"),
	Bard UMETA(DisplayName = "Bard"),
	Sorcerer UMETA(DisplayName = "Sorcerer"),
	Druid UMETA(DisplayName = "Druid")
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = "Class defaults")
	TSubclassOf<UGameplayEffect> GEPrimaryAttributes;
};

UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
#pragma region Default Region
	UPROPERTY(EditDefaultsOnly, Category = "Common Defaults")
	TSubclassOf<UGameplayEffect> GESecondAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Common Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Common Defaults")
	TSubclassOf<UGameplayEffect> GEVitalAttributes;
#pragma endregion

#pragma region Class Region
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> ClassDefaults;

	UFUNCTION(BlueprintCallable, Category = "Class Defaults")
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);

	UPROPERTY(EditDefaultsOnly, Category = "Damage Calculation|Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;
#pragma endregion
};
