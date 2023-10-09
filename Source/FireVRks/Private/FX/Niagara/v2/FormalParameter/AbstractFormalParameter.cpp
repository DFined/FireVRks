#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"

UAbstractParameterValue* UAbstractFormalParameter::DefaultValue() const
{
	return Default;
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

UAbstractFormalParameter::~UAbstractFormalParameter()
{
	delete(Predicate);
}

FString UAbstractFormalParameter::GetDisplayName()
{
	return DisplayName;
}
