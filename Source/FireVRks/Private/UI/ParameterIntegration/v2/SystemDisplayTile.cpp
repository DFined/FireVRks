#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"

#include "DFUI/DFUI.h"
#include "UI/CoreUI/SystemPicker.h"

void USystemDisplayTile::OpenSystemSelection(UClickableSystemTile* Tile)
{
	USystemPicker::SelectSystem(Tile);
}

UPanelWidget* USystemDisplayTile::MakeRootWidget()
{
	OuterBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(OuterBorder, DFStyleUtil::GREY_LVL_1);
	
	SystemTile = DFUI::AddWidget<UClickableSystemTile>(OuterBorder);
	SystemTile->GetOnPressed().AddUniqueDynamic(this, &USystemDisplayTile::OpenSystemSelection);
	return OuterBorder; 
}

void USystemDisplayTile::SetSystem(UEffectSystem* System, int Size)
{
	SystemTile->Initialize(System, Size);
}
