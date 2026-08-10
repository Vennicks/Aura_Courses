


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/AttributeSetBase.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAttributeSetBase::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Vigor = 0;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	Vigor = FMath::Max(Vigor, 0.f);

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject()))
	{
		int32 PlayerLevel = CombatInterface->GetCharacterLevel();

		return 80.f + 2.5 * Vigor + 10.f * PlayerLevel;
	}
	return 80.f;
}
