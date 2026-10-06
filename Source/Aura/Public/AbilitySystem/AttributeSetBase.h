

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"

 #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

template<class T>
using TStaticFunctPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


UCLASS()
class AURA_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAttributeSetBase();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	TMap<FGameplayTag, TStaticFunctPtr<FGameplayAttribute()>> TagsToAttributes;

#pragma region Attributes Definition
#pragma  region Vital Attributes Definition

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Mana;

	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Mana);

#pragma endregion

#pragma  region Primary Attributes Definition

	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Strength;

	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;

	UPROPERTY(ReplicatedUsing = OnRep_Resilience, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;

	UPROPERTY(ReplicatedUsing = OnRep_Vigor, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;


	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Strength);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Intelligence);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Resilience);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Vigor);

#pragma endregion

#pragma  region Secondary Attributes Definition

	UPROPERTY(ReplicatedUsing = OnRep_Armor, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Armor;

	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData ArmorPenetration;

	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData BlockChance;

	UPROPERTY(ReplicatedUsing = OnRep_CritChance, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData CritChance;

	UPROPERTY(ReplicatedUsing = OnRep_CritDamage, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData CritDamage;

	UPROPERTY(ReplicatedUsing = OnRep_CritResistence, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData CritResistence;

	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData HealthRegeneration;

	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData ManaRegeneration;

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;


	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Armor);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, ArmorPenetration);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, BlockChance);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, CritChance);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, CritDamage);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, CritResistence);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, HealthRegeneration);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, ManaRegeneration);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxMana);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth);

#pragma endregion

#pragma region Meta Attributes Definition 
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;

	ATTRIBUTE_ACCESSORS(UAttributeSetBase, IncomingDamage)
#pragma endregion
#pragma endregion

protected:
#pragma region Replication
#pragma  region Vital Attributes Replication

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

#pragma endregion

#pragma  region Primary Attributes Replication

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

#pragma endregion

#pragma  region Secondary Attributes Replication

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const;

	UFUNCTION()
	void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const;

	UFUNCTION()
	void OnRep_CritResistence(const FGameplayAttributeData& OldCritResistence) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

#pragma endregion
#pragma endregion

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
