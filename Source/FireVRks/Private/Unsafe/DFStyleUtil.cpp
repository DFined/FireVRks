#include "Unsafe/DFStyleUtil.h"

#include "Components/HorizontalBoxSlot.h"
#include "Engine/Font.h"

FLinearColor DFStyleUtil::GREY_LVL_N0 = FLinearColor(0.011833f, 0.011833f, 0.011833f);
FLinearColor DFStyleUtil::GREY_LVL_0 = FLinearColor(0.020833f, 0.020833f, 0.020833f);
FLinearColor DFStyleUtil::GREY_LVL_1 = FLinearColor(0.029, 0.029, 0.029);
FLinearColor DFStyleUtil::GREY_LVL_2 = FLinearColor(0.036458f, 0.036458f, 0.036458f);
FLinearColor DFStyleUtil::GREY_LVL_3 = FLinearColor(0.06, 0.06, 0.06);
FLinearColor DFStyleUtil::GREY_LVL_4 = FLinearColor(0.140000f, 0.140000f, 0.140000f, 0);
FLinearColor DFStyleUtil::GREY_OUTLINE_LVL_0 = FLinearColor(0.015f, 0.015f, 0.015f);

FLinearColor DFStyleUtil::LIGHT_TEXT_1 = FLinearColor(200, 200, 200);
FSlateFontInfo DFStyleUtil::DEFAULT_FONT = FSlateFontInfo(Cast<UObject>(LoadObject<UFont>(NULL, TEXT("/Game/FireVRks/UI/Font/DefaultFont.DefaultFont"))), 12, "Roboto");

void DFStyleUtil::LineBorderStyle(UBorder* Border)
{
	auto Brush = FSlateBrush();
	Brush.DrawAs = ESlateBrushDrawType::RoundedBox;

	auto Outline = FSlateBrushOutlineSettings(
		FVector4(0.f, 0.f, 0.f, 1.f), FSlateColor(DFStyleUtil::GREY_OUTLINE_LVL_0), 1.0
	);
	Outline.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
	Brush.OutlineSettings = Outline;

	Border->SetBrush(Brush);
	Border->SetBrushColor(GREY_LVL_2);
	Border->SetPadding(FMargin(9, 2));
}

void DFStyleUtil::BasicBorderStyle(UBorder* Border, ESlateBrushDrawType::Type DrawType, FLinearColor Color)
{
	auto Brush = FSlateBrush();
	Brush.DrawAs = DrawType;
	Border->SetBrush(Brush);
	Border->SetBrushColor(Color);
}

void DFStyleUtil::TextBoxStyle(UEditableTextBox* TextBox)
{
	TextBox->SetJustification(ETextJustify::Center);

	FSlateBrush NormalBrush = FSlateBrush();
	NormalBrush.DrawAs = ESlateBrushDrawType::RoundedBox;

	auto Outline = FSlateBrushOutlineSettings(FVector4(3.f, 3.f, 3.f, 3.f), GREY_OUTLINE_LVL_0, 1);
	Outline.RoundingType = ESlateBrushRoundingType::FixedRadius;
	NormalBrush.OutlineSettings = Outline;

	TextBox->SetMinDesiredWidth(100);

	TextBox->WidgetStyle = FEditableTextBoxStyle()
		.SetBackgroundColor(GREY_LVL_0)
		.SetPadding(FMargin(2, 0))
		.SetFont(DEFAULT_FONT)
		.SetBackgroundImageNormal(NormalBrush)
		.SetTextStyle(
			FTextBlockStyle()
			.SetFont(DEFAULT_FONT)
			.SetColorAndOpacity(FSlateColor(LIGHT_TEXT_1))
		);
}

void DFStyleUtil::TextBlockStyle(UTextBlock* TextBlock)
{
	TextBlock->SetFont(DEFAULT_FONT);
}

void DFStyleUtil::CheckBoxStyle(UCheckBox* TextBlock)
{
	auto Style = TextBlock->GetWidgetStyle();
	Style.SetPadding(FMargin(0));
	auto Brush = Style.BackgroundImage;
	Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
	Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	Brush.OutlineSettings.CornerRadii = FVector4(4,4,4,4);
	Brush.OutlineSettings.Color = GREY_LVL_3;
	Brush.OutlineSettings.Width = 1;
	Brush.TintColor = GREY_LVL_4;
	Style.SetBackgroundImage(Brush);
	Style.SetBackgroundHoveredImage(Brush);
	Style.SetBackgroundPressedImage(Brush);
	Style.SetForegroundColor(GREY_LVL_N0);
	TextBlock->SetWidgetStyle(Style);
}

template <class SlotType>
void DFStyleUtil::SetPadding(UWidget* Widget, FMargin Margin)
{
	auto Slot = Cast<SlotType>(Widget->Slot);
	if(Slot)
	{
		Slot->SetPadding(Margin);
	}
}
