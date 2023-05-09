#pragma once
#include "AbstractFormalParameter.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContext.h"
#include "FX/Niagara/SystemSettings/ParameterValues/ParameterValue.h"

template <typename Type>
class FormalParameter : public AbstractFormalParameter
{
	AbstractParameterValue* AbstractValue;
protected:
	Type DefaultValue;

public:
	FormalParameter(const FString& GUID, FString Name, DFType ValueType, bool IsRequired, Type DefValue, bool bManaged)
		: AbstractFormalParameter(GUID, Name, ValueType, IsRequired, bManaged)
	{
		DefaultValue =  DefValue;
		AbstractValue = new ParameterValue<Type>(DefaultValue, ValueType, true);
	}

	explicit FormalParameter(DFType ValueType, FString Name, bool IsRequired, Type DefValue, bool bManaged)
		: AbstractFormalParameter(FGuid::NewGuid().ToString(), Name, ValueType, IsRequired, bManaged)
	{
		DefaultValue = DefValue;
		AbstractValue = new ParameterValue<Type>(DefaultValue, ValueType, true);
	}

	Type GetValue(ParameterValueContext* ValueContext)
	{
		auto Value = ValueContext->Get(this);
		if (Value)
		{
			return static_cast<ParameterValue<Type>*>(Value)->Get();
		}
		return DefaultValue;
	}

	virtual AbstractParameterValue* GetDefault() override;

	virtual ~FormalParameter() override;

	
};
