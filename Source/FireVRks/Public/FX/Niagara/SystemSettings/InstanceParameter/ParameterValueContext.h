#pragma once
#include "FX/Niagara/SystemSettings/FormalParameter/AbstractFormalParameter.h"
#include "FX/Niagara/SystemSettings/ParameterValues/AbstractParameterValue.h"

class AbstractFormalParameter;
/**
 * An object that supplies values for formal parameters
 */
class ParameterValueContext : public DFTyped
{
public:
	explicit ParameterValueContext(bool bManaged)
		: DFTyped(bManaged)
	{
	}

	virtual ~ParameterValueContext() override = default;

	
	/**
	 * Get the value for the specified parameter in this context or nullptr if it is absent
	 */
	virtual AbstractParameterValue* Get(AbstractFormalParameter* Parameter);;
	virtual AbstractParameterValue* GetInternal(FGuid ParameterId, DFType Type) PURE_VIRTUAL("GetInternal", return __nullptr;);
	virtual AbstractParameterValue* GetById(FGuid ParameterId, DFType Type, AbstractParameterValue* Default);

	virtual AbstractParameterValue* SetValue(FGuid ParameterId, AbstractParameterValue*) = 0;

	virtual DFType GetType() override;


	template <class Type>
	Type* GetValue(AbstractFormalParameter* Parameter)
	{
		auto Value = this->Get(Parameter);
		if (!Value)
		{
			Value = Parameter->GetDefault();
		}
		return static_cast<Type*>(Value);
	}
};
