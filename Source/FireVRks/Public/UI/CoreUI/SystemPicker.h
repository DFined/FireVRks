// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/UniformGridPanel.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "UI/ParameterIntegration/v2/ClickableSystemTile.h"
#include "SystemPicker.generated.h"

/**
 * 
 */
UCLASS()
class FIREVRKS_API USystemPicker : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* Border;

	UPROPERTY()
	UUniformGridPanel* Grid;
	
	UPROPERTY()
	TArray<UEffectSystem*> Systems = TArray<UEffectSystem*>();

	int Columns = 8;
	int TileSize = 96;

	int SelectedX;
	int SelectedY;

public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;

	UFUNCTION()
	void OnSelectSystem(UClickableSystemTile* Tile);
	void SetSystems();

	static void SelectSystem(UObject* Object)
	{
		auto Ctrlr = UGameplayStatics::GetPlayerController(Object->GetWorld(), 0);
		auto Popup = UDFUIUtil::OpenInputPopup<USystemPicker>(Ctrlr, "Select an effect system");
		Popup->GetWidget<USystemPicker>()->SetSystems();
		
	}
};
