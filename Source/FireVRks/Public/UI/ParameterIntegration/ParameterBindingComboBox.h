#pragma once
#include "ParameterBindingWidget.h"
#include "Components/ComboBoxString.h"
#include "FX/Niagara/SystemSettings/Enums/EnumLike.h"
#include "ParameterBindingComboBox.generated.h"

UCLASS()
class UParameterBindingComboBox : public UComboBoxString, public ParameterBindingWidget
{
	GENERATED_BODY()

public:
	UParameterBindingComboBox(const FObjectInitializer& ObjectInitializer)
		: UComboBoxString(ObjectInitializer)
	{
		OnSelectionChanged.AddUniqueDynamic(this, &UParameterBindingComboBox::HandleSelectionChangedInternal);
	}

private:
	EnumLike* EnumType;
public:
	virtual void SetValue(AbstractParameterValue* Value) override;

	virtual void Initialize(ParameterValueContext* Value, AbstractFormalParameter* Parameter) override;

	virtual UWidget* AsWidget() override;

	virtual void DefaultStyle() override;

	virtual AbstractParameterValue* GetValue() override;

	UFUNCTION()
	void HandleSelectionChangedInternal(FString SelectedItem, ESelectInfo::Type SelectionType)
	{
		if(SelectionType != ESelectInfo::Direct)
		{
			OnChange();
		}
	}	
};
