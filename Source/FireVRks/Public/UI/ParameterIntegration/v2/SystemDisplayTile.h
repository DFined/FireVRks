#pragma once
#include "ClickableSystemTile.h"
#include "Components/Border.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "DFUI/DFUIBase.h"
#include "SystemDisplayTile.generated.h"

UCLASS()
class FIREVRKS_API USystemDisplayTile : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* OuterBorder;

	UPROPERTY()
	UClickableSystemTile* SystemTile;
public:
	UFUNCTION()
	void OpenSystemSelection(UClickableSystemTile* Tile);
	virtual UPanelWidget* MakeRootWidget() override;

	void SetSystem(UEffectSystem* System, int IconSize);
	
};
