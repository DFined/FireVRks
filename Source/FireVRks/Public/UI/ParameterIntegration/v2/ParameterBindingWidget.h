#pragma once
#include "ParameterDrawType.h"
#include "Blueprint/UserWidget.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "DFUI/DFUIBase.h"
#include "ParameterBindingWidget.generated.h"


UCLASS()
class FIREVRKS_API UParameterBindingWidget : public UDFUIBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UAbstractFormalParameter* Parameter;

	UPROPERTY()
	UParameterValueContext* Context;

	ParameterDrawType DrawType;
	
public:
	virtual UPanelWidget* MakeRootWidget() override PURE_VIRTUAL("MakeRootWidget", return nullptr;);

	virtual UPanelWidget* GetMountingPoint() override PURE_VIRTUAL("GetMountingPoint", return nullptr;);

	virtual void Setup(UAbstractFormalParameter* FParameter, UParameterValueContext* Context, ParameterDrawType DrawType);
	
	virtual void InitializeBindingWidget() PURE_VIRTUAL("Initialize",);

	virtual void WriteToContext(UParameterValueContext* bContext) PURE_VIRTUAL("WriteToContext",);

	virtual void DefaultStyle();

	UAbstractFormalParameter* GetParameter() const;

	virtual void OnChange();

	UParameterValueContext*& GetContext();
};
