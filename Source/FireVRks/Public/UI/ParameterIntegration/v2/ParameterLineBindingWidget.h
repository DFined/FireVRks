#pragma once
#include "ParamBindingSelectionWidget.h"
#include "ParameterBindingWidget.h"
#include "WidgetWithValue.h"
#include "Components/Border.h"
#include "Event/DFEvent.h"
#include "ParameterLineBindingWidget.generated.h"

UCLASS()
class FIREVRKS_API UParameterLineBindingWidget : public UParameterBindingWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* Border;

	WidgetWithValue* ChildWidget;
	
	UPROPERTY()
	UParamBindingSelectionWidget* BindSelector;

public:
	UFUNCTION()
	void OnDelete();
	UFUNCTION()
	void MoveUp();
	UFUNCTION()
	void MoveDown();
	void UnbindParameter();
	UFUNCTION()
	void ProcessSystemEvent(UDFEvent* Event);

	UFUNCTION()
	void OnParamBound(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnParameterNameChanged(const FText& Text, ETextCommit::Type CommitMethod);
	virtual void InitializeBindingWidget() override;
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;
	virtual void WriteToContext(UParameterValueContext* Context) override;
	void RedrawParentBlock();
	virtual void OnChange() override;
};
