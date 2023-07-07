#pragma once
#include "Blueprint/UserWidget.h"
#include "DFUIBase.generated.h"
/**
 * Base class for DFUI. Basically a setup method for a root widget
 */

UCLASS(Abstract, Blueprintable)
class UDFUIBase : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY()
	UPanelWidget* RootContainer;

	virtual TSharedRef<SWidget> RebuildWidget() override;


public:

	
	/**
	 * Either get an existing root panel-widget or setup a new one
	*/
	virtual UPanelWidget* GetOrCreateRoot();

	/**
	 * Construct the root widget
	*/
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) PURE_VIRTUAL("MakeRootWidget", return nullptr;);
	
	virtual void RebuildWidgetInternal();

	virtual void BaseInit();
};
