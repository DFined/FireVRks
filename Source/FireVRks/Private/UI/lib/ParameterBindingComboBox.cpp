#include "UI/lib/ParameterBindingComboBox.h"

#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/ParameterValue/EnumParameterValue.h"
#include "UI/lib/DFStyleUtil.h"

void UParameterBindingComboBox::Initialize(UAbstractParameterValue* Value)
{
	auto Val = Cast<UEnumParameterValue>(Value);
	
	EnumType = Val->Get()->GetParent();
	auto Names = EnumType->GetNames();
	for(FString Name: *Names)
	{
		this->AddOption(Name);		
	}
	SetValue(Value);
}


void UParameterBindingComboBox::SetValue(UAbstractParameterValue* Value)
{
	SetSelectedOption(UParamUtil::GetTypedValue<UEnumParameterValue, EnumLikeValue*>(Value)->Name);
}

void UParameterBindingComboBox::DefaultStyle()
{
	this->ContentPadding = FMargin(0);
	this->Font = DFStyleUtil::DEFAULT_FONT;
	this->ItemStyle.SetTextColor(DFStyleUtil::LIGHT_TEXT_1);
	FSlateBrush& Style = this->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal;
	Style.DrawAs = ESlateBrushDrawType::RoundedBox;
	Style.TintColor = DFStyleUtil::GREY_LVL_0;
	Style.OutlineSettings.Color = DFStyleUtil::GREY_LVL_2;
	Style.OutlineSettings.Width = 2;

	FSlateBrush& HoveredStyle = this->WidgetStyle.ComboButtonStyle.ButtonStyle.Hovered;
	HoveredStyle.TintColor = DFStyleUtil::GREY_LVL_0;
	HoveredStyle.OutlineSettings.Color = DFStyleUtil::GREY_LVL_2;
	HoveredStyle.OutlineSettings.Width = 2;

	FSlateBrush& PressedStyle = this->WidgetStyle.ComboButtonStyle.ButtonStyle.Pressed;
	PressedStyle.TintColor = DFStyleUtil::GREY_LVL_0;
	PressedStyle.OutlineSettings.Color = DFStyleUtil::GREY_LVL_2;
	PressedStyle.OutlineSettings.Width = 2;
	
	this->ForegroundColor = DFStyleUtil::LIGHT_TEXT_1;
}

UAbstractParameterValue* UParameterBindingComboBox::GetValue(UParameterValueContext* Context)
{
	FString Value = this->GetSelectedOption();
	return UEnumParameterValue::New(Context, EnumType->Get(Value));
}

UWidget* UParameterBindingComboBox::AsWidget()
{
	return this;
}
