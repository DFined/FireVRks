#include "UI/ParameterIntegration/ParameterBindingComboBox.h"

#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"
#include "FX/Niagara/SystemSettings/FormalParameter/EnumFormalParameter.h"
#include "Unsafe/DFStyleUtil.h"
#include "Unsafe/ParameterIntegration/ParameterTypingUtil.h"

void UParameterBindingComboBox::SetValue(AbstractParameterValue* Value)
{
	auto Val = ParameterTypingUtil::ToValue<EnumLikeValue*>(Value);
	SetSelectedOption(Val->Get()->Name);	
}

void UParameterBindingComboBox::Initialize(ParameterValueContext* Value, AbstractFormalParameter* Paramt)
{
	auto Param = static_cast<EnumFormalParameter*>(Paramt);
	EnumType = Param->GetEnumType();
	auto Names = EnumType->GetNames();
	for(FString Name: *Names)
	{
		this->AddOption(Name);		
	}
	ParameterBindingWidget::Initialize(Value, Paramt);
}


UWidget* UParameterBindingComboBox::AsWidget()
{
	return this;
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

AbstractParameterValue* UParameterBindingComboBox::GetValue()
{
	FString Value = this->GetSelectedOption();
	return new ParameterValue(EnumType->Get(Value), DFType::TYPED_ENUM_PARAMETER, false);
}
