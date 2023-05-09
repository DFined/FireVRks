#pragma once
#include "DFUIContainer.h"
#include "Components/VerticalBox.h"
#include "DFUIStack.generated.h"

UCLASS(Blueprintable)
class UDFUIStack : public UDFUIContainer
{
	GENERATED_BODY()

	UPROPERTY()
	UVerticalBox* VerticalBox;
	
public:
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) override;
	virtual UPanelWidget* GetMountingPoint() override;
	virtual UPanelSlot* Append(UWidget* Widget) override;
};
