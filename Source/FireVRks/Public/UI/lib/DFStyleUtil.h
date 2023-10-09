#pragma once
#include "Icon.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
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

	static void LineBorderStyle(UBorder* Border);
	static void BasicBorderStyle(UBorder* Border, ESlateBrushDrawType::Type DrawType, FLinearColor Color);
	static void TextBoxStyle(UEditableTextBox* Border);
	static void TextBlockStyle(UTextBlock* TextBlock);
	static void CheckBoxStyle(UCheckBox* TextBlock);
	static void TextButtonStyle(UButton* Button, FLinearColor Color);
	static void ImgButtonStyle(UButton* Button, Icon* Icon, float size);

	static FSlateBrush SetupImageBrush(UTexture2D* Icon, float size);

	static UTexture2D* LoadCachedTexture(Icon* Icon);
	
	static void SafeSetVBoxSlotWidth(TObjectPtr<UPanelSlot> Slot, FSlateChildSize SlateChildSize);

	static UTexture2D* DEFAULT_TEXTURE;

	static void SafeSetHBoxSlotWidth(UPanelSlot* Slot, FSlateChildSize Size);
	static void SafeSetVBoxSlotAlignment(UPanelSlot* Slot, EHorizontalAlignment Alignment);

	template<class SlotType>
	static void SetPadding(UWidget* Widget, FMargin Margin);
};
