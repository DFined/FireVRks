#pragma once
#include "Components/CheckBox.h"
#include "UI/ParameterIntegration/ParameterBindingWidget.h"
#include "ParameterBindingCheckbox.generated.h"

UCLASS()
class UParameterBindingCheckbox : public UCheckBox, public ParameterBindingWidget
{
	GENERATED_BODY()
public:
	UParameterBindingCheckbox(const FObjectInitializer& ObjectInitializer)
		: UCheckBox(ObjectInitializer),
		  ParameterBindingWidget()
	{
		this->OnCheckStateChanged.AddUniqueDynamic(this, &UParameterBindingCheckbox::HandleCheckStateChanged);
	}
	virtual void SetValue(AbstractParameterValue* Value) override;

	virtual void DefaultStyle() override;

	virtual UWidget* AsWidget() override;

	virtual AbstractParameterValue* GetValue() override;
	

	UFUNCTION()
	virtual void HandleCheckStateChanged(bool bIsChecked);
};
