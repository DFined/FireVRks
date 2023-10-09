#pragma once
#include "DFAnchor.generated.h"

/**
 * Dummy anchor object as a top level for all statics
 */
UCLASS()
class FIREVRKS_API UDFAnchor : public UObject
{
	GENERATED_BODY()

public:
	static UDFAnchor* Instance()
	{
		auto Anchor = NewObject<UDFAnchor>(GetTransientPackage(), "DFStaticOuterAnchor");
		Anchor->AddToRoot();
		return Anchor;
	}
};
