#include "FX/Niagara/v2/MapParameterValueContext.h"

#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"

UAbstractParameterValue* UMapParameterValueContext::Get(UAbstractFormalParameter* Parameter)
{
	auto Id = Parameter->GetId();
	if (Map.Contains(Id))
	{
		auto Val = Map.Find(Id);
		if (Val)
		{
			return *Val;
		}
	}
	auto Val = Parameter->DefaultValue()->Clone(Parameter);
	Map.Add(Id, Val);
	return Val;
}

void UMapParameterValueContext::SetValue(UAbstractFormalParameter* Parameter, UAbstractParameterValue* Value)
{
	Map.Add(Parameter->GetId(), Value);
}

void UMapParameterValueContext::SetValue(FDFId Parameter, UAbstractParameterValue* Value)
{
	Map.Add(Parameter, Value);
}

TSharedPtr<FJsonObject> UMapParameterValueContext::ToJson()
{
	auto Obj = MakeShareable(new FJsonObject());
	auto Keys = TArray<FDFId>();
	Map.GetKeys(Keys);
	for(auto Id : Keys)
	{
		auto Val = *Map.Find(Id);
		Obj.Object->SetObjectField(Id.GetId(), Val->ToJson());
	}
	return Obj;
}
