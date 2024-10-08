#include "UI/lib/ValidatedTextBox/ValidatedTextBox.h"

#include "FX/Niagara/v2/ParameterValue/IntParameterValue.h"
#include "DFUI/DFUI.h"
#include "DFUI/DFStyleUtil.h"
#include "Widgets/Input/SEditableTextBox.h"

UValidatedTextBox::UValidatedTextBox(): Validator()
{
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


void UValidatedTextBox::SetValue(FString Value)
{
	this->SetText(FText::FromString(Value));
}

void UValidatedTextBox::SetValue(UAbstractParameterValue* Value)
{
	SetValue(ValueToString(Value));
}

void UValidatedTextBox::DefaultStyle()
{
	DFStyleUtil::TextBoxStyle(this);
}

UWidget* UValidatedTextBox::AsWidget()
{
	return this;
}

void UValidatedTextBox::OnChange()
{
	this->NotifyOfChange(this);
}

void UValidatedTextBox::Initialize(UAbstractParameterValue* Value)
{
	PrevText = ValueToString(Value);
	SetValue(PrevText);
}


