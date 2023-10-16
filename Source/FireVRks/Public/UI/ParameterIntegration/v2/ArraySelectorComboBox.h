// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetWithValue.h"
#include "Components/ComboBoxString.h"
#include "World/Launcher/GenericLauncherArray.h"
#include "ArraySelectorComboBox.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API UArraySelectorComboBox : public UComboBoxString, public WidgetWithValue
{
	GENERATED_BODY()
	
	static FString NONE_OPTION_NAME;
public:
	UArraySelectorComboBox();

	virtual void DefaultStyle() override;
	void ReInitOptions(UGenericLauncherArray* Array);

	UFUNCTION()
	void ReInit();
	virtual void Initialize(UAbstractParameterValue* Value) override;
	virtual UAbstractParameterValue* GetValue(UParameterValueContext* Context) override;
	virtual void SetValue(UAbstractParameterValue* Value) override;
	virtual UWidget* AsWidget() override;

	UFUNCTION()
	void HandleSelectionChangedInternal(FString SelectedItem, ESelectInfo::Type SelectionType);
};
