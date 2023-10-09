#pragma once
#include "AbstractParameterValue.h"
#include "IntParameterValue.generated.h"

UCLASS()
class FIREVRKS_API UIntParameterValue : public UAbstractParameterValue
{
	GENERATED_BODY()
	int Value;
	
public:
	int Get() const;

	void SetValue(int Value);

	static UIntParameterValue* New(UObject* Outer, int Value);

	friend bool operator==(const UIntParameterValue& Lhs, const UIntParameterValue& RHS)
	{
		return Lhs.Value == RHS.Value;
	}

	friend bool operator!=(const UIntParameterValue& Lhs, const UIntParameterValue& RHS)
	{
		return !(Lhs == RHS);
	}
};
