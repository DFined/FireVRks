#pragma once
#include "WidgetCallbackWithValue.h"
#include "Components/Widget.h"
#include "FX/Niagara/SystemSettings/FormalParameter/AbstractFormalParameter.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "FX/Niagara/SystemSettings/ParameterValues/AbstractParameterValue.h"

class ParameterBindingWidget
{
protected:
	AbstractFormalParameter* Parameter;
	TArray<WidgetCallbackWithValue*> Callbacks;

public:
	virtual ~ParameterBindingWidget() = default;

	explicit ParameterBindingWidget(): Parameter(nullptr)
	{
	}

	virtual void SetValue(AbstractParameterValue* Value)
	{
	}

	virtual void Initialize(ParameterValueContext* Context, AbstractFormalParameter* Param)
	{
		this->SetValue(Context->Get(Param));
		this->Parameter = Param;
	}

	virtual UWidget* AsWidget() { return nullptr; }

	virtual void DefaultStyle()
	{
	}

	virtual void SetValueInContext(MapParameterValueContext* Context)
	{
		Context->SetValue(this->Parameter->GetGUID(), this->GetValue());
	};

	virtual AbstractParameterValue* GetValue() {return nullptr;};

	virtual void OnChange()
	{
		for(WidgetCallbackWithValue* Callback: Callbacks)
		{
			Callback->Callback(this, GetValue());
		}
	}
	
	virtual void SubscribeToChanges(WidgetCallbackWithValue* Callback);
};
