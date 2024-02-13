#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"

#include "FX/Niagara/v2/ParamUtil.h"


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

TSharedPtr<FJsonObject> UIntParameterValue::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetNumberField("Value", Value);
	Obj->SetStringField("Type", UParamUtil::Name(INTEGER));
	return MakeShareable<FJsonObject>(Obj);
}

int UIntParameterValue::ValueFromJson(TSharedPtr<FJsonObject> Obj)
{
	return Obj->GetIntegerField("Value");
}

UAbstractParameterValue* UIntParameterValue::Clone(UAbstractFormalParameter* Param)
{
	return New(Param, this->Value);
}
