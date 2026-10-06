


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagsHolder.h"
#include "AbilitySystem/AbilitySystemLibrary.h"
#include "AbilitySystem/AttributeSetBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct GameDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritResistence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritChance);

	GameDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CritResistence, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CritDamage, Source, false);
	}
};

static const GameDamageStatics DamageStatics()
{
	static GameDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritResistenceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const auto SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const auto TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	auto SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	auto TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const auto& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	//Get damage
	float Damage = Spec.GetSetByCallerMagnitude(FGameplayTagsHolder::Get().Damage);

	//Capture BlockChance from target
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.0f, TargetBlockChance);

	//Get Coefficients from CharacterClassInfo
	UCharacterClassInfo* CharacterClassInfo = UAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	auto ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	auto EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float ArmorPenetration = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetCharacterLevel());
	const float EffectiveArmorCoef = EffectiveArmorCurve->Eval(SourceCombatInterface->GetCharacterLevel());

	if (FMath::RandRange(0.f, 100.f) < TargetBlockChance)
	{
		Damage /= ArmorPenetration;
	}

	//capture armor
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.0f, TargetArmor);

	//capture armor penetration
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.0f, SourceArmorPenetration	);

	const float EffectiveArmor = TargetArmor * (100.f - SourceArmorPenetration * EffectiveArmorCoef) / 100.f;
	Damage *= (100 - EffectiveArmor) / 100;

	float SourceCriticalHitChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(0.0f, SourceCriticalHitChance);

	float TargetCriticalResistence = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritResistenceDef, EvaluationParameters, TargetCriticalResistence);
	TargetCriticalResistence = FMath::Max<float>(0.0f, TargetCriticalResistence);

	float CriticalDamage = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, EvaluationParameters, CriticalDamage);
	CriticalDamage = FMath::Max<float>(0.0f, CriticalDamage);	

	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalResistence;
	Damage = FMath::RandRange(1, 100) < EffectiveCriticalHitChance ? Damage * 2 + CriticalDamage : Damage;


	const FGameplayModifierEvaluatedData EvaluatedData(UAttributeSetBase::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);

}
