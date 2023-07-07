#pragma once
#include "ParameterBindingWidget.h"
#include "ParameterRenderer.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/System/EffectSystem.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/SimplePVCProvider.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "ParameterInputUI.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UParameterInputUI : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UVerticalBox* VerticalBox;

	MapParameterValueContext* Context = nullptr;

	UPROPERTY()
	UEffectSystem* System;
	
public:
	UParameterInputUI();

	virtual ~UParameterInputUI() override;

	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	void WriteParamsToContext(MapParameterValueContext* bContext);

	void DumpToContext();

	void Draw(ParameterValueContext* Context);

	void OnChildWidgetValueChange(ParameterBindingWidget* Widget, AbstractParameterValue* Value);

	void SetSystem(UEffectSystem* FSystem)
	{
		this->System = FSystem;
	}

	UFUNCTION(BlueprintCallable)
	void SpawnSystem(AActor* Target);

	void SubscribeToChanges(WidgetCallbackWithValue* Callback);

	

	UParameterValueContextProvider* GetContextProvider();
	void CleanUp();
};

