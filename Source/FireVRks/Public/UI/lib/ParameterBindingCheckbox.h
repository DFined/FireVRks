#pragma once
#include "Components/CheckBox.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "UI/ParameterIntegration/v2/WidgetWithValue.h"
#include "ParameterBindingCheckbox.generated.h"

UCLASS()
class FIREVRKS_API UParameterBindingCheckbox : public UCheckBox, public WidgetWithValue
{
	GENERATED_BODY()
public:
	UParameterBindingCheckbox(const FObjectInitializer& ObjectInitializer)
		: UCheckBox(ObjectInitializer)
	{
		this->OnCheckStateChanged.AddUniqueDynamic(this, &UParameterBindingCheckbox::HandleCheckStateChanged);
	}
	virtual void SetValue(UAbstractParameterValue* Value) override;

	virtual void DefaultStyle() override;

	virtual UAbstractParameterValue* GetValue(UObject* Outer) override;

	virtual void Initialize(UAbstractParameterValue* Value) override;


	UFUNCTION()
	virtual void HandleCheckStateChanged(bool bIsChecked);

	virtual UWidget* AsWidget() override;
};
