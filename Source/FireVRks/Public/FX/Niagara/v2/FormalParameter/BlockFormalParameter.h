#pragma once
#include "AbstractFormalParameter.h"
#include "BlockFormalParameter.generated.h"

UCLASS()
class FIREVRKS_API UBlockFormalParameter : public UAbstractFormalParameter
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UAbstractFormalParameter*> ChildParameters;
	
public:

	void Add(UAbstractFormalParameter* Child);

	TArray<UAbstractFormalParameter*> GetChildParameters() const
	{
		return ChildParameters;
	}

	static UBlockFormalParameter* New(UObject* Outer, bool Expanded);
};
