#pragma once
#include "DFUIParameterBindingWidgetBase.h"
#include "ParameterBindingWidget.h"
#include "Components/ExpandableArea.h"
#include "Components/HorizontalBox.h"
#include "UI/lib/Container/DFUIStack.h"
#include "ParameterBindingBlock.generated.h"

class UParameterBindingList;

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

	UPROPERTY()
	UHorizontalBox* HeaderBox;

	UPROPERTY()
	UParameterBindingList* ParentList = nullptr;

	
public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;

	virtual void Initialize(ParameterValueContext* Value, AbstractFormalParameter* Param) override;

	virtual void SetValueInContext(MapParameterValueContext* Context) override;

	virtual void SubscribeToChanges(WidgetCallbackWithValue* Callback) override;

	void MakeListItem(UParameterBindingList* PList);

	UFUNCTION()
	void OnDelete();

	virtual void CleanUp() override;
};
