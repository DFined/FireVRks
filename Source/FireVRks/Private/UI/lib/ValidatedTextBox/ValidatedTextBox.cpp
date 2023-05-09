#include "UI/lib/ValidatedTextBox/ValidatedTextBox.h"

#include "Unsafe/DFStyleUtil.h"
#include "Unsafe/ParameterIntegration/ParameterTypingUtil.h"
#include "Widgets/Input/SEditableTextBox.h"

UWidget* UValidatedTextBox::AsWidget()
{
	return this;
}

UValidatedTextBox::UValidatedTextBox(const FObjectInitializer& Initializer): ParameterBindingWidget()
{
}

TSharedRef<SWidget> UValidatedTextBox::RebuildWidget()
{
	return Super::RebuildWidget();
}

void UValidatedTextBox::HandleOnTextCommitted(const FText& NewText, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::OnCleared)
	{
		if (Validator(NewText.ToString()))
		{
			MyEditableTextBlock->SetText(NewText);
			PrevText = NewText.ToString();
			Super::HandleOnTextCommitted(NewText, CommitMethod);
			OnChange();
		}
		else
		{
			MyEditableTextBlock->SetText(FText::FromString(PrevText));
		}
	}
}

FString UValidatedTextBox::ToValue(AbstractParameterValue* Value)
{
	return ParameterTypingUtil::GetParamUtil(Value->GetType())->ToString(Value);
}

void UValidatedTextBox::SetValue(AbstractParameterValue* Value)
{
	this->SetText(FText::FromString(ToValue(Value)));
}

void UValidatedTextBox::DefaultStyle()
{
	DFStyleUtil::TextBoxStyle(this);
}

void UValidatedTextBox::Initialize(ParameterValueContext*  Context, AbstractFormalParameter* Param)
{
	PrevText = ToValue(Context->Get(Param));
	ParameterBindingWidget::Initialize(Context, Param);
}

