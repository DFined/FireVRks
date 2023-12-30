#pragma once
#include "DFStyleUtil.h"
#include "Components/ComboBoxString.h"
#include "FX/Niagara/SystemSettings/Enums/EnumLike.h"
#include "FX/Niagara/v2/ParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/AbstractParameterValue.h"
#include "UI/ParameterIntegration/v2/WidgetWithValue.h"
#include "ParameterBindingComboBox.generated.h"

UCLASS()
class FIREVRKS_API UParameterBindingComboBox : public UComboBoxString, public WidgetWithValue
{
	GENERATED_BODY()

public:
	UParameterBindingComboBox(const FObjectInitializer& ObjectInitializer)
		: UComboBoxString(ObjectInitializer)
	{
		OnSelectionChanged.AddUniqueDynamic(this, &UParameterBindingComboBox::HandleSelectionChangedInternal);
		DFStyleUtil::ComboBox(this);
	}

private:
	EnumLike* EnumType;
public:
	virtual void SetValue(UAbstractParameterValue* Value) override;
	virtual void Initialize(UAbstractParameterValue* Value) override;

	virtual void DefaultStyle() override;

	virtual UAbstractParameterValue* GetValue(UObject* Outer) override;

	UFUNCTION()
	void HandleSelectionChangedInternal(FString SelectedItem, ESelectInfo::Type SelectionType)
	{
		if(SelectionType != ESelectInfo::Direct)
		{
			NotifyOfChange(this);
		}
	}

	virtual UWidget* AsWidget() override;
};
