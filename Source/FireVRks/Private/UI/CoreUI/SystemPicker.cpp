// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreUI/SystemPicker.h"

#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "DFUI/DFUI.h"
#include "UI/ParameterIntegration/v2/ClickableSystemTile.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"

UPanelWidget* USystemPicker::MakeRootWidget()
{
	Border = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(Border, DFStyleUtil::GREY_LVL_1);
	Grid = DFUI::AddWidget<UUniformGridPanel>(Border);
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
	
	SelectedSystem = Tile->GetEffectSystem();

	Tile->Select();
}

void USystemPicker::SetSystems()
{
	Grid->ClearChildren();
	Systems.Empty();
	
	UEffectSystemManager::GetInstance()->List(Systems);
	int x = 0;
	int y = 0;
	for(UEffectSystem* System : Systems)
	{
		auto Tile = DFUI::MakeWidget<UClickableSystemTile>(this);
		Grid->AddChildToUniformGrid(Tile, x, y);
		Tile->Initialize(System);
		Tile->GetOnPressed().AddUniqueDynamic(this, &USystemPicker::OnSelectSystem);
		
		x++;
		if(x == Columns)
		{
			x = 0;
			y++;
		}
	}
}

void USystemPicker::OnSelected(UWidget* Widget)
{
	auto Picker = Cast<USystemPicker>(Widget);
	this->OnSelectComplete.Broadcast(Picker->SelectedSystem);
}

USystemPicker* USystemPicker::SelectSystem(UObject* Object)
{
	auto Ctrlr = UGameplayStatics::GetPlayerController(Object->GetWorld(), 0);
	auto Popup = EDFUI::OpenInputPopup<USystemPicker>(Ctrlr, "Select an effect system");
	auto Picker = Popup->GetWidget<USystemPicker>();
	Picker->SetSystems();
	Popup->GetOnConfirm()->AddUniqueDynamic(Picker, &USystemPicker::OnSelected);
	return Picker;
}

FOnSelectSystemDelegate& USystemPicker::GetOnSelectComplete()
{
	return OnSelectComplete;
}


