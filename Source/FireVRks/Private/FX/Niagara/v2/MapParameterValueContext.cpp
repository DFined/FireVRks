#include "FX/Niagara/v2/MapParameterValueContext.h"

#include "FX/Niagara/v2/ParamUtil.h"
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
	for (auto Id : Keys)
	{
		auto Val = *Map.Find(Id);
		if (Val->IsSerializable())
		{
			Obj.Object->SetObjectField(Id.GetId(), Val->ToJson());
		}
	}
	return Obj;
}

UParameterValueContext* UMapParameterValueContext::Clone(UObject* Parent)
{
	auto Context = NewObject<UMapParameterValueContext>(Parent);
	DFU::CloneMap(this->Map, Context->Map);
	return Context;
}

UParameterValueContext* UMapParameterValueContext::FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer)
{
	auto Context = Instance(Outer);
	for (auto Entry : Json->Values)
	{
		auto Key = FDFId::Named(Entry.Key);
		auto DummyOuters = TMap<FDFId, UAbstractFormalParameter*>();
		auto Value = UParamUtil::ValueFromJson(Entry.Value->AsObject(), Context, DummyOuters);
		Context->SetValue(*Key.Get(), Value);
	}	
	return Context;
}
