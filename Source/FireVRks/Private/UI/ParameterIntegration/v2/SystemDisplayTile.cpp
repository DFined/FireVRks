#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"

#include "UI/DFUIUtil.h"
#include "UI/CoreUI/SystemPicker.h"

void USystemDisplayTile::OpenSystemSelection(UClickableSystemTile* Tile)
{
	USystemPicker::SelectSystem(Tile);
}

UPanelWidget* USystemDisplayTile::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, DFStyleUtil::GREY_LVL_1);
	
	SystemTile = UDFUIUtil::AddUserWidget<UClickableSystemTile>(OuterBorder);
	SystemTile->GetOnPressed().AddUniqueDynamic(this, &USystemDisplayTile::OpenSystemSelection);
	return OuterBorder; 
}

void USystemDisplayTile::SetSystem(UEffectSystem* System, int Size)
{
	SystemTile->Initialize(System, Size);
}
