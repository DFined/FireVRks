#pragma once
#include "DFUIParameterBindingWidgetBase.h"
#include "ParameterBindingBlock.h"
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "UI/lib/Container/DFUIStack.h"
#include "ParameterBindingList.generated.h"

UCLASS()
class UParameterBindingList : public UDFUIParameterBindingWidgetBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* OuterBorder;

	UPROPERTY()
	UDFUIStack* ListStack;

	UParameterBindingBlock* AddWidgetFromParam(ParameterValueContext* PVC, BlockCompoundParameter* Param);

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;

	virtual void Initialize(ParameterValueContext* Value, AbstractFormalParameter* Param) override;

	virtual void SetValueInContext(MapParameterValueContext* Context) override;

	virtual void SubscribeToChanges(WidgetCallbackWithValue* Callback) override;

	UFUNCTION()
	void RemoveItem(UDFUIParameterBindingWidgetBase* Widget);

	UFUNCTION()
	void NewItem();

	virtual ~UParameterBindingList() override;

	virtual void CleanUp() override;
};
