#pragma once
#include "DFUIParameterBindingWidgetBase.h"
#include "ParameterBindingWidget.h"
#include "Components/Border.h"
#include "Components/ExpandableArea.h"
#include "UI/lib/Container/DFUIStack.h"
#include "ParameterBindingBlock.generated.h"

UCLASS()
class  UParameterBindingBlock : public UDFUIParameterBindingWidgetBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* OuterBorder;

	UPROPERTY()
	UDFUIStack* RequiredParamsStack;
	
	UPROPERTY()
	UDFUIStack* OverrideParamsStack;

	UPROPERTY()
	UExpandableArea* OverridesTab;

	UPROPERTY()
	UExpandableArea* BaseTab;

	
public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;

	virtual void Initialize(ParameterValueContext* Value, AbstractFormalParameter* Param) override;

	virtual void SetValueInContext(MapParameterValueContext* Context) override;

	virtual void SubscribeToChanges(WidgetCallbackWithValue* Callback) override;
};
