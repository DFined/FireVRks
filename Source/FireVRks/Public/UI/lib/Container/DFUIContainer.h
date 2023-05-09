#pragma once
#include "DFUIBase.h"
#include "Blueprint/UserWidget.h"
#include "DFUIContainer.generated.h"

/**
 * Base polymorphic wrapper for simple DF-UI containers
 */
UCLASS(Abstract)
class UDFUIContainer : public UDFUIBase
{
	GENERATED_BODY()
	
protected:
	virtual void RebuildWidgetInternal() override;
	
public:
	
	/**
	 * Construct the root widget
	*/
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) PURE_VIRTUAL("MakeRootWidget", return nullptr;);
	
	UFUNCTION(BlueprintCallable)
	virtual UPanelSlot* Append(UWidget* Widget);

	UFUNCTION(BlueprintCallable)
	virtual UPanelWidget* GetMountingPoint() PURE_VIRTUAL("GetMountingPoint", return nullptr;);
	
	virtual void BaseInit() override;
};
