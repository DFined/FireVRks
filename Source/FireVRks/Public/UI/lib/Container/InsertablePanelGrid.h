#pragma once
#include "DFUI/DFUIBase.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "UI/lib/Container/WidgetArray.h"
#include "InsertablePanelGrid.generated.h"


/**
 * Clusterf*** of a class to implement the main UI. TODO: rewrite this when I figure out a better way to do this
 */
UCLASS()
class FIREVRKS_API UInsertablePanelGrid : public UDFUIBase
{
	GENERATED_BODY()
	
	inline static int X_SPACING = 30;
	inline static int Y_SPACING = 30;
	inline static int BUTTON_SIZE = 32;

	UPROPERTY()
	UCanvasPanel* Panel;	
	UPROPERTY()
	TArray<UWidgetArray*> Children;
	UPROPERTY()
	TArray<UButton*> PlusButtons = TArray<UButton*>();

	UCanvasPanelSlot* GetSlot(int X, int Y);

	void MakePlusButton(int X, int Y);

public:
	UFUNCTION(BlueprintCallable)
	void AddColumn(UWidget* Widget, int PosX);

	UFUNCTION(BlueprintCallable)
	void AddWidget(UWidget* Widget, int PosX, int PosY);

	UFUNCTION(BlueprintCallable)
	int GetWidthForColumn(int X);

	int GetWidth(int X, int Y);
	int GetHeight(int X, int Y);

	void setSize(int X, int Y, int Width, int Height);

	UFUNCTION(BlueprintCallable)
	void ReTile();

	virtual UPanelWidget* MakeRootWidget() override;

	virtual UPanelWidget* GetMountingPoint() override;
};
