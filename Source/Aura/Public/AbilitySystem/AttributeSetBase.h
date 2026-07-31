

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

UCLASS()
class AURA_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAttributeSetBase();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Mana;

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;

	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Mana);
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxMana);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
