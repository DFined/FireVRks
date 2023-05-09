#pragma once
#include "Components/EditableTextBox.h"
#include "UI/ParameterIntegration/ParameterBindingWidget.h"
#include "ValidatedTextBox.generated.h"

UCLASS()
class UValidatedTextBox : public UEditableTextBox, public ParameterBindingWidget
{
public:
	virtual UWidget* AsWidget() override;

private:
	GENERATED_BODY()
	bool(* Validator)(FString);
	FString PrevText;
public:
	explicit UValidatedTextBox(const FObjectInitializer& Initializer);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void HandleOnTextCommitted(const FText& NewText, ETextCommit::Type CommitMethod) override;
public:	
	explicit UValidatedTextBox(const FObjectInitializer& Initializer, bool(*ValidatorFunc)(FString))
		: UEditableTextBox(Initializer), ParameterBindingWidget(), Validator(ValidatorFunc)
	{
	}
	
	FString ToValue(AbstractParameterValue* Value);


	virtual void SetValue(AbstractParameterValue* Value) override;

	virtual void Initialize(ParameterValueContext* Context, AbstractFormalParameter* Parameter) override;

	virtual void DefaultStyle() override;
};
