// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreUI/SystemPicker.h"

#include "Components/UniformGridSlot.h"
#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/ClickableSystemTile.h"
#include "Util/DFStatics.h"

UPanelWidget* USystemPicker::MakeRootWidget(UWidgetTree* Tree)
{
	Border = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(Border, DFStyleUtil::GREY_LVL_1);
	Grid = UDFUIUtil::AddWidget<UUniformGridPanel>(Tree, Border);
	Grid->SetSlotPadding(FMargin(5,5,5,5));
	return Border;
}

UPanelWidget* USystemPicker::GetMountingPoint()
{
	return Grid;
}

void USystemPicker::OnSelectSystem(UClickableSystemTile* Tile)
{
	for(auto Child : Grid->GetAllChildren())
	{
		Cast<UClickableSystemTile>(Child)->DeSelect();
	}
	auto TileSlot = Cast<UUniformGridSlot>(Tile->Slot);
	this->SelectedX = TileSlot->GetColumn();
	this->SelectedY = TileSlot->GetRow();

	Tile->Select();
}

void USystemPicker::SetSystems()
{
	Grid->ClearChildren();
	Systems.Empty();
	
	UDFStatics::EFFECT_SYSTEM_MANAGER->List(Systems);
	int x = 0;
	int y = 0;
	for(UEffectSystem* System : Systems)
	{
		auto Tile = UDFUIUtil::MakeUserWidget<UClickableSystemTile>(this);
		Grid->AddChildToUniformGrid(Tile, x, y);
		Tile->Initialize(System, TileSize);
		Tile->GetOnPressed().AddUniqueDynamic(this, &USystemPicker::OnSelectSystem);
		
		x++;
		if(x == Columns)
		{
			x = 0;
			y++;
		}
	}
}


