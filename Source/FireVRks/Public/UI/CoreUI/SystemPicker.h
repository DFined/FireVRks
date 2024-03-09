// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/UniformGridPanel.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DFUI/DFUI.h"
#include "DFUI/DFUIBase.h"
#include "UI/EDFUI.h"
#include "UI/ParameterIntegration/v2/ClickableSystemTile.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"
#include "SystemPicker.generated.h"

class FOnSelectSystemDelegate;
/**
 * 
 */
UCLASS()
class FIREVRKS_API USystemPicker : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* Border;

	UPROPERTY()
	UUniformGridPanel* Grid;
	
	UPROPERTY()
	TArray<UEffectSystem*> Systems = TArray<UEffectSystem*>();

	UPROPERTY()
	UEffectSystem* SelectedSystem;

	FOnSelectSystemDelegate OnSelectComplete;

	int Columns = 8;
	int TileSize = 96;

	

public:
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;

	UFUNCTION()
	void OnSelectSystem(UClickableSystemTile* Tile);
	void SetSystems();

	UFUNCTION()
	void OnSelected(UWidget* Widget);
	static USystemPicker* SelectSystem(UObject* Object);

	FOnSelectSystemDelegate& GetOnSelectComplete();
};
