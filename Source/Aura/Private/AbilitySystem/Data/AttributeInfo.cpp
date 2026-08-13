


#include "AbilitySystem/Data/AttributeInfo.h"

FAttributeInfoStruct UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (auto AttributeInfo : AttributeInfos)
	{
		if (AttributeInfo.AttributeTag.MatchesTagExact(Tag))
		{
			return AttributeInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute info not found for tag: %s"), *Tag.ToString());
	}

	return FAttributeInfoStruct();
}
