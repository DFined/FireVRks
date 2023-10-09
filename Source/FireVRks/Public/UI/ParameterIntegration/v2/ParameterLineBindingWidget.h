#pragma once
#include "ParameterBindingWidget.h"
#include "WidgetWithValue.h"
#include "Components/Border.h"
#include "ParameterLineBindingWidget.generated.h"

UCLASS()
class FIREVRKS_API UParameterLineBindingWidget : public UParameterBindingWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* Border;

	WidgetWithValue* ChildWidget;
public:
	virtual void Initialize(UAbstractFormalParameter* Parameter, UParameterValueContext* Context) override;
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
	virtual void WriteToContext(UParameterValueContext* Context) override;
};
