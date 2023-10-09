#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "UI/lib/Container/DFUIContainer.h"
#include "DFUILine.generated.h"

UCLASS(Blueprintable)
/**
 * Custom wrapper around a Horizontal box intended for linear settings editors
 */
class FIREVRKS_API UDFUILine : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UHorizontalBox* HBox;


public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
};
