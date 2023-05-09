#pragma once
#include "Components/Border.h"
#include "Components/CheckBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

class DFStyleUtil
{
public:
	static FLinearColor GREY_OUTLINE_LVL_0;
	static FLinearColor GREY_LVL_N0;
	static FLinearColor GREY_LVL_0;
	static FLinearColor GREY_LVL_1;
	static FLinearColor GREY_LVL_2;
	static FLinearColor GREY_LVL_3;
	static FLinearColor GREY_LVL_4;

	static void LineBorderStyle(UBorder* Border);
	static void BasicBorderStyle(UBorder* Border, ESlateBrushDrawType::Type DrawType, FLinearColor Color);
	static void TextBoxStyle(UEditableTextBox* Border);
	static void TextBlockStyle(UTextBlock* TextBlock);
	static void CheckBoxStyle(UCheckBox* TextBlock);
	static FLinearColor LIGHT_TEXT_1;
	static FSlateFontInfo DEFAULT_FONT;

	template<class SlotType>
	static void SetPadding(UWidget* Widget, FMargin Margin);
};
