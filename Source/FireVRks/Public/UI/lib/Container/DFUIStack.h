#pragma once
#include "DFUI/DFUIBase.h"
#include "Components/VerticalBox.h"
#include "DFUIStack.generated.h"

UCLASS(Blueprintable)
class FIREVRKS_API UDFUIStack : public UDFUIBase
{
	GENERATED_BODY()

	UPROPERTY()
	UVerticalBox* VerticalBox;
	
public:
	virtual UPanelWidget* MakeRootWidget() override;
	virtual UPanelWidget* GetMountingPoint() override;
	virtual UPanelSlot* Append(UWidget* Widget) override;
};
