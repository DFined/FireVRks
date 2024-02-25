#pragma once
#include "ClickableSystemTile.h"
#include "Components/Border.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "DFUI/DFUIBase.h"
#include "SystemDisplayTile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectSystemDelegate, UEffectSystem*, System);

UCLASS()
class FIREVRKS_API USystemDisplayTile : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBorder* OuterBorder;

	UPROPERTY()
	UClickableSystemTile* SystemTile;

	UPROPERTY()
	FOnSelectSystemDelegate OnSelectionChanged;
	
public:
	UFUNCTION()
	void OpenSystemSelection(UClickableSystemTile* Tile);
	UFUNCTION()
	void OnSelectComplete(UEffectSystem* System);
	virtual UPanelWidget* MakeRootWidget() override;

	void SetSystem(UEffectSystem* System, int IconSize);

	FOnSelectSystemDelegate& GetOnSelectionChanged();
};
