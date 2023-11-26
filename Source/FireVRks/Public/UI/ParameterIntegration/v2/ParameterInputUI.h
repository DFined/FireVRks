#pragma once
#include "ParameterControlWidget.h"
#include "UI/lib/Container/DFUIContainer.h"
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
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	
	virtual UPanelWidget* GetMountingPoint() override;

	void DumpToContext();
	void WriteToContext(UParameterValueContext* FillContext);

	void Draw(UParameterValueContext* InitialContext);
	virtual void OnChange() override;

	void SetProvider(ParameterProvider* bProvider)
	{
		this->Provider = bProvider;
	}
};
