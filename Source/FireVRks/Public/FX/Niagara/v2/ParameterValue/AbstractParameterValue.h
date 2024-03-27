#pragma once
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "AbstractParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UAbstractParameterValue : public UObject
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<FJsonObject> ToJson()
	{
		return TSharedPtr<FJsonObject>(new FJsonObject);
	}

	virtual UAbstractParameterValue* Clone(UAbstractFormalParameter* Param) PURE_VIRTUAL("Clone", return nullptr;);

	virtual bool IsSerializable();
};
