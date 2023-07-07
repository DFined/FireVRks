#pragma once
#include "DFUIParameterBindingWidgetBase.h"
#include "ParameterBindingWidget.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "SingleParameterBindingWidget.generated.h"

UCLASS()
class USingleParameterBindingWidget : public UDFUIParameterBindingWidgetBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* Border;
	ParameterBindingWidget* ChildWidget;
public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;

	virtual void Initialize(ParameterValueContext* Value, AbstractFormalParameter* Parameter) override;

	virtual AbstractParameterValue* GetValue() override;

	virtual void SubscribeToChanges(WidgetCallbackWithValue* Callback) override;

	virtual void CleanUp() override;
};
