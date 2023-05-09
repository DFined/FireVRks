#pragma once
#include "ParameterBindingWidget.h"
#include "ParameterRenderer.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "ParameterInputUI.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UParameterInputUI : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UVerticalBox* VerticalBox;

	TArray<AbstractFormalParameter*> Parameters;
	MapParameterValueContext* Context = __nullptr;
public:
	UParameterInputUI();

	virtual ~UParameterInputUI() override;

	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	void WriteParamsToContext(MapParameterValueContext* bContext);

	void AddParameter(AbstractFormalParameter* Parameter);
	void AddParameters(TArray<AbstractFormalParameter*> Parameter);

	void DumpToContext();

	void Draw(ParameterValueContext* Context);

	void OnChildWidgetValueChange(ParameterBindingWidget* Widget, AbstractParameterValue* Value);

	UFUNCTION(BlueprintCallable)
	UDefaultParameterSystem* GetSystem();
};

