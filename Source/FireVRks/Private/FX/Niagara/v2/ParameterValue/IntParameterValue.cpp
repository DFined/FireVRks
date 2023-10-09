#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"


int UIntParameterValue::Get() const
{
	return Value;
}

void UIntParameterValue::SetValue(int bValue)
{
	this->Value = bValue;
}

UIntParameterValue* UIntParameterValue::New(UObject* Outer, int Value)
{
	auto Val = NewObject<UIntParameterValue>(Outer, StaticClass());
	Val->SetValue(Value);
	return Val;
}
