


#include "Inputs/InputConfig.h"

const UInputAction* UInputConfig::GetInputActionTag(FGameplayTag& InputTag)
{
	for (const FLinkInputAction& Link : InputActions)
	{
		if (Link.InputAction && Link.InputTag == InputTag)
		{
			return Link.InputAction;
		}
	}
	return nullptr;
}
