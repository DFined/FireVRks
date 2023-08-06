#pragma once
#include "FX/Niagara/System/ParameterProvider.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "Components/VerticalBox.h"
#include "ParameterInputUI.generated.h"

UCLASS()
class UParameterInputUI : public UDFUIContainer
{
	GENERATED_BODY()
	
	MapParameterValueContext* Context = nullptr;

	UPROPERTY()
	UVerticalBox* VerticalBox;

	ParameterProvider* ParamProvider;
public:
	UParameterInputUI();

	virtual ~UParameterInputUI() override;
	
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	
	virtual UPanelWidget* GetMountingPoint() override;

	void WriteParamsToContext(MapParameterValueContext* bContext);

	void DumpToContext();

	void Draw(ParameterValueContext* Context);

	void OnChildWidgetValueChange(ParameterBindingWidget* Widget, AbstractParameterValue* Value);

	void SetProvider(ParameterProvider* Provider)
	{
		this->ParamProvider = Provider;
	}

	void SubscribeToChanges(WidgetCallbackWithValue* Callback);

	
	UParameterValueContextProvider* GetContextProvider();
	
	void CleanUp();
};
