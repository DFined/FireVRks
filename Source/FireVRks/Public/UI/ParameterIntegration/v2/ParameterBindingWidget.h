#pragma once
#include "Blueprint/UserWidget.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "ParameterBindingWidget.generated.h"

UCLASS()
class FIREVRKS_API UParameterBindingWidget : public UDFUIContainer
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UAbstractFormalParameter* Parameter;
	
public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override PURE_VIRTUAL("MakeRootWidget", return nullptr;);

	virtual UPanelWidget* GetMountingPoint() override PURE_VIRTUAL("GetMountingPoint", return nullptr;);

	virtual void Setup(UAbstractFormalParameter* FParameter, UParameterValueContext* Context);
	
	virtual void Initialize(UAbstractFormalParameter* fParameter, UParameterValueContext* Context) PURE_VIRTUAL("Initialize",);

	virtual void WriteToContext(UParameterValueContext* Context) PURE_VIRTUAL("WriteToContext",);

	virtual void DefaultStyle();

	UAbstractFormalParameter* GetParameter() const;

	virtual void OnChange() override;
};
