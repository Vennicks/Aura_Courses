


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/AttributeSetBase.h"
#include "Interaction/CombatInterface.h"


UMMC_MaxMana::UMMC_MaxMana()
{
	IntelDef.AttributeToCapture = UAttributeSetBase::GetIntelligenceAttribute();
	IntelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(IntelDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intel = 0;
	GetCapturedAttributeMagnitude(IntelDef, Spec, EvaluationParameters, Intel);
	Intel = FMath::Max(Intel, 0.f);

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject()))
	{
		int32 PlayerLevel = CombatInterface->GetCharacterLevel();

		return 50.f + 2.5 * Intel + 15.f * PlayerLevel;
	}
	return 50.f;
}
