#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"

#include "Components/Image.h"
#include "UI/DFUIUtil.h"

UPanelWidget* USystemDisplayTile::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_2);
	return OuterBorder; 
}

void USystemDisplayTile::SetSystem(UEffectSystem* System, int Size)
{
	auto Box = DFUIUtil::AddWidget<UVerticalBox>(WidgetTree, OuterBorder);
	auto Name = DFUIUtil::AddLabel(WidgetTree, Box, System->GetDisplayName());
	DFStyleUtil::TextBlockStyle(Name);
	
	auto Icon = DFUIUtil::AddWidget<UImage>(WidgetTree, Box);
	Icon->SetBrush(DFStyleUtil::SetupImageBrush(System->GetIcon(), Size));
	DFStyleUtil::SafeSetVBoxSlotAlignment(Icon->Slot, HAlign_Center);
}
