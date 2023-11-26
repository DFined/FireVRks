#pragma once
#include "ListParameterBindingWidget.h"
#include "ParameterBindingWidget.h"
#include "Components/ExpandableArea.h"
#include "Components/HorizontalBox.h"
#include "BlockParameterBindingWidget.generated.h"

UCLASS()
class FIREVRKS_API UBlockParameterBindingWidget : public UParameterBindingWidget
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

	UPROPERTY()
	UHorizontalBox* HeaderBox;

	
public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
	UFUNCTION()
	void LayoutChangedTab(UExpandableArea* Area, bool bIsExpanded);
	virtual void InitializeBindingWidget(UAbstractFormalParameter* Parameter, UParameterValueContext* Context, ParameterDrawType DrawType) override;
	virtual void WriteToContext(UParameterValueContext* Context) override;
	void Redraw();
};
