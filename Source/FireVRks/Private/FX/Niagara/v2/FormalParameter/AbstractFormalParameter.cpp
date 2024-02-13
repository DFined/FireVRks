#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ColorFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/FloatFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/IntFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "FX/Niagara/v2/ParameterValue/BlockParameterValue.h"
#include "FX/Niagara/v2/ParameterValue/FloatParameterValue.h"

UAbstractParameterValue* UAbstractFormalParameter::DefaultValue() const
{
	return Default;
}

void UAbstractFormalParameter::SetDefault(UAbstractParameterValue* bDefault)
{
	this->Default = bDefault;
}

UDFId* UAbstractFormalParameter::GetId()
{
	return Id;
}

ParameterPredicate* UAbstractFormalParameter::GetPredicate() const
{
	return Predicate;
}

void UAbstractFormalParameter::SetPredicate(ParameterPredicate* fPredicate)
{
	this->Predicate = fPredicate;
}

bool UAbstractFormalParameter::IsRequired() const
{
	return Required;
}

void UAbstractFormalParameter::SetRequired(bool bRequired)
{
	Required = bRequired;
}

ParameterType UAbstractFormalParameter::GetType() const
{
	return Type;
}

void UAbstractFormalParameter::SetId(UDFId* fId)
{
	this->Id = fId;
}

void UAbstractFormalParameter::SetType(ParameterType fType)
{
	this->Type = fType;
}

void UAbstractFormalParameter::SetDisplayName(const FString& fDisplayName)
{
	this->DisplayName = fDisplayName;
}

TSharedPtr<FJsonObject> UAbstractFormalParameter::ToJson()
{
	auto Obj = new FJsonObject();
	Obj->SetStringField("Id", GetId()->GetId());
	Obj->SetStringField("DisplayName", GetDisplayName());
	Obj->SetStringField("Type", UParamUtil::Name(GetType()));
	Obj->SetObjectField("DefaultValue", Default->ToJson());
	return MakeShareable(Obj);
}

UAbstractFormalParameter::~UAbstractFormalParameter()
{
	delete(Predicate);
}

UAbstractFormalParameter* UAbstractFormalParameter::FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer)
{
	auto Type = UParamUtil::TypeFromName(Json->GetStringField("Type"));
	auto Value = Json->GetObjectField("DefaultValue");
	UAbstractFormalParameter* Param;
	switch (Type)
	{
	case INTEGER: Param = UIntFormalParameter::New(Outer, UIntParameterValue::ValueFromJson(Value));
		break;
	case FLOAT: Param = UFloatFormalParameter::New(Outer, UFloatParameterValue::ValueFromJson(Value));
		break;
	case BOOLEAN: Param = UBoolFormalParameter::New(Outer, UBoolParameterValue::ValueFromJson(Value));
		break;
	case COLOR: Param = UColorFormalParameter::New(Outer, UColorParameterValue::ValueFromJson(Value));
		break;
	case BLOCK: Param = UBlockFormalParameter::New(Outer, UBlockParameterValue::ValueFromJson(Value));
		break;
	default: throw std::invalid_argument("Non basic parameter type cannot be deserialized");
	}
	Param->SetId(UDFId::Named(Param, Json->GetStringField("Id")));
	Param->SetDisplayName(Json->GetStringField("DisplayName"));
	return Param;
}

FString UAbstractFormalParameter::GetDisplayName()
{
	return DisplayName;
}
