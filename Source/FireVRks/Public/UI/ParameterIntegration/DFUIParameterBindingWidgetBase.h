#pragma once
#include "ParameterBindingWidget.h"
#include "UI/lib/Container/DFUIBase.h"
#include "DFUIParameterBindingWidgetBase.generated.h"

UCLASS()
class UDFUIParameterBindingWidgetBase : public UDFUIBase, public ParameterBindingWidget
{
	GENERATED_BODY()

protected:
	virtual void RebuildWidgetInternal() override;

public:
	virtual void BaseInit() override;
	
	virtual UWidget* AsWidget() override;

	virtual AbstractParameterValue* GetValue() override;

	virtual void SubscribeToChanges(WidgetCallbackWithValue* Callback) override;

	virtual void CleanUp() override;
};
