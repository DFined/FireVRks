#pragma once
#include "Icon.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"

class DFStyleUtil
{
	static TMap<FString, UTexture2D*> CachedTextures;
public:
	static FLinearColor GREY_OUTLINE_LVL_0;
	static FLinearColor GREY_LVL_N0;
	static FLinearColor GREY_LVL_0;
	static FLinearColor GREY_LVL_1;
	static FLinearColor GREY_LVL_2;
	static FLinearColor GREY_LVL_3;
	static FLinearColor GREY_LVL_4;
	static FLinearColor LIGHT_TEXT_1;
	static FSlateFontInfo DEFAULT_FONT;

	static FLinearColor SELECTED_LEVEL_3;

	static void LineBorderStyle(UBorder* Border);
	static void BasicBorderStyle(UBorder* Border, FLinearColor Color);
	static void RoundedBorderStyle(UBorder* Border, FLinearColor Color, int radius);
	static void TextBoxStyle(UEditableTextBox* Border);
	static void TextBlockStyle(UTextBlock* TextBlock);
	static void CheckBoxStyle(UCheckBox* TextBlock);
	static void TextButtonStyle(UButton* Button, FLinearColor Color);
	static void ImgButtonStyle(UButton* Button, UTexture2D* Img, float size);
	static void ImgButtonStyle(UButton* Button, Icon* Icon, float size);

	static FSlateBrush SetupImageBrush(UTexture2D* Icon, float size);

	static UTexture2D* LoadCachedTexture(Icon* Icon);
	
	static void SafeSetVBoxSlotWidth(TObjectPtr<UPanelSlot> Slot, FSlateChildSize SlateChildSize);

	static UTexture2D* DEFAULT_TEXTURE;

	static void SafeSetHBoxSlotWidth(UPanelSlot* Slot, FSlateChildSize Size);
	static void SafeSetHBoxSlotWidth(UPanelSlot* Slot, FSlateChildSize Size, EHorizontalAlignment Alignment);
	static void SafeSetHBoxSlotWidth(UPanelSlot* Slot, FSlateChildSize Size, EHorizontalAlignment HAlignment, EVerticalAlignment VAlignment);
	static void SafeSetVBoxSlotAlignment(UPanelSlot* Slot, EHorizontalAlignment Alignment);

	template<class SlotType>
	static void SetPadding(UWidget* Widget, FMargin Margin);

	static void ComboBox(UComboBoxString* Box)
	{
		Box->ContentPadding = FMargin(0);
		Box->Font = DEFAULT_FONT;
		Box->ItemStyle.SetTextColor(LIGHT_TEXT_1);
		FSlateBrush& Style = Box->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal;
		Style.DrawAs = ESlateBrushDrawType::RoundedBox;
		Style.TintColor = GREY_LVL_0;
		Style.OutlineSettings.Color = GREY_LVL_2;
		Style.OutlineSettings.Width = 2;
		Box->WidgetStyle.ContentPadding = FMargin(0);

		FSlateBrush& HoveredStyle = Box->WidgetStyle.ComboButtonStyle.ButtonStyle.Hovered;
		HoveredStyle.TintColor = GREY_LVL_0;
		HoveredStyle.OutlineSettings.Color = GREY_LVL_2;
		HoveredStyle.OutlineSettings.Width = 2;

		FSlateBrush& PressedStyle = Box->WidgetStyle.ComboButtonStyle.ButtonStyle.Pressed;
		PressedStyle.TintColor = GREY_LVL_0;
		PressedStyle.OutlineSettings.Color = GREY_LVL_2;
		PressedStyle.OutlineSettings.Width = 2;
	
		Box->ForegroundColor = LIGHT_TEXT_1;
	}
};
