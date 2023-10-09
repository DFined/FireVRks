#pragma once
#include "DFAnchor.generated.h"

/**
 * Dummy anchor object as a top level for all statics
 */
UCLASS()
class FIREVRKS_API UDFAnchor : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UObject*> Children;
	
public:
	static UDFAnchor* Instance();

	void Anchor(UObject* Object);;
};
