#pragma once
#include "DFUIBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "UI/ParameterIntegration/DFUIParameterBindingWidgetBase.h"
#include "DFUIContainer.generated.h"

/**
 * Base polymorphic wrapper for simple DF-UI containers
 */
UCLASS(Abstract)
class UDFUIContainer : public UDFUIBase
{
	GENERATED_BODY()
	
public:
	
	/**
	 * Construct the root widget
	*/
	virtual UPanelWidget* MakeRootWidget(UWidgetTree* Tree) PURE_VIRTUAL("MakeRootWidget", return nullptr;);
	
	UFUNCTION(BlueprintCallable)
	virtual UPanelSlot* Append(UWidget* Widget);

	UFUNCTION(BlueprintCallable)
	virtual UPanelWidget* GetMountingPoint() PURE_VIRTUAL("GetMountingPoint", return nullptr;);

	void CleanUpBindingWidgets()
	{
		for (UWidget* AllChild : this->GetMountingPoint()->GetAllChildren()) 
		{
			auto PBW = static_cast<UDFUIParameterBindingWidgetBase*>(AllChild);
			PBW->CleanUp();
			PBW->RemoveFromParent();
		}
	}
};
