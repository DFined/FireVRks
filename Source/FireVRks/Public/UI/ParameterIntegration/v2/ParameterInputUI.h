#pragma once
#include "ParameterControlWidget.h"
#include "ParameterDrawType.h"
#include "DFUI/DFUIBase.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/v2/System/ParameterProvider.h"
#include "ParameterInputUI.generated.h"

UCLASS()
class FIREVRKS_API UParameterInputUI : public UParameterControlWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UVerticalBox* VerticalBox;
	
protected:
	UPROPERTY()
	UParameterValueContext* Context = nullptr;

	ParameterProvider* Provider;
	
public:	
	virtual UPanelWidget* MakeRootWidget() override;
	
	virtual UPanelWidget* GetMountingPoint() override;

	UFUNCTION(BlueprintCallable)
	void DumpToContext();
	void WriteToContext(UParameterValueContext* FillContext);

	void Draw(UParameterValueContext* InitialContext);
	void Draw(UParameterValueContext* InitialContext, ParameterDrawType DrawType);
	virtual void OnChange() override;

	void SetProvider(ParameterProvider* bProvider)
	{
		this->Provider = bProvider;
	}

	UFUNCTION(BlueprintCallable)
	UParameterValueContext* GetContext() 
	{
		return Context;
	}
};
