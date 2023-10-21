#pragma once
#include "Components/EditableTextBox.h"
#include "UI/ParameterIntegration/v2/WidgetWithValue.h"
#include "ValidatedTextBox.generated.h"

UCLASS(Abstract)
class FIREVRKS_API UValidatedTextBox : public UEditableTextBox, public WidgetWithValue
{
	GENERATED_BODY()
	
	bool (*Validator)(FString);

public:
	explicit UValidatedTextBox();

protected:
	virtual void HandleOnTextCommitted(const FText& NewText, ETextCommit::Type CommitMethod) override;
	FString PrevText;


public:
	explicit UValidatedTextBox(const FObjectInitializer& Initializer, bool (*ValidatorFunc)(FString))
		: UEditableTextBox(Initializer), Validator(ValidatorFunc)
	{
	}

	virtual void SetValue(FString Value);

	virtual void Initialize(UAbstractParameterValue* Value) override;
	virtual FString ValueToString(UAbstractParameterValue* Value) PURE_VIRTUAL("ValueToString", return "";);
	virtual UAbstractParameterValue* GetValue(UParameterValueContext* Context) override PURE_VIRTUAL("GetValue", return nullptr;);
	virtual void SetValue(UAbstractParameterValue* Value) override;

	virtual void DefaultStyle() override;

	virtual UWidget* AsWidget() override;

	virtual void OnChange();
};
