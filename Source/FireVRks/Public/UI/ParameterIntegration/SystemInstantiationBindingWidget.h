#pragma once
#include "DFUIParameterBindingWidgetBase.h"
#include "EffectParameterInputUI.h"
#include "FX/Niagara/System/EffectSystem.h"
#include "SystemInstantiationBindingWidget.generated.h"

UCLASS()
class USystemInstantiationBindingWidget : public UDFUIParameterBindingWidgetBase
{
	GENERATED_BODY()

	UPROPERTY()
	UEffectSystem* System;
	
	UPROPERTY()
	UBorder* OuterBorder;

	UPROPERTY()
	UEffectParameterInputUI* InstanceParamUI;
	
public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;

	virtual void Initialize(ParameterValueContext* Context, AbstractFormalParameter* Param) override;

	virtual void SetValueInContext(MapParameterValueContext* Context) override;

	virtual void SubscribeToChanges(WidgetCallbackWithValue* Callback) override;

	virtual void CleanUp() override;
};
