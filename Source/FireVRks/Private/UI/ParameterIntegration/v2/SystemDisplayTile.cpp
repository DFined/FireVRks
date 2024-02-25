#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"

#include "DFUI/DFUI.h"
#include "UI/CoreUI/SystemPicker.h"

void USystemDisplayTile::OpenSystemSelection(UClickableSystemTile* Tile)
{
	auto Picker = USystemPicker::SelectSystem(Tile);
	Picker->GetOnSelectComplete().AddUniqueDynamic(this, &USystemDisplayTile::OnSelectComplete);
}

void USystemDisplayTile::OnSelectComplete(UEffectSystem* System)
{
	SetSystem(System, 96);
	OnSelectionChanged.Broadcast(System);
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

FOnSelectSystemDelegate& USystemDisplayTile::GetOnSelectionChanged()
{
	return OnSelectionChanged;
}
