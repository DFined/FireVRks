#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "DFUI/DFUIBase.h"
#include "DFUILine.generated.h"

UCLASS(Blueprintable)
/**
 * Custom wrapper around a Horizontal box intended for linear settings editors
 */
class FIREVRKS_API UDFUILine : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UHorizontalBox* HBox;


public:
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;
};
