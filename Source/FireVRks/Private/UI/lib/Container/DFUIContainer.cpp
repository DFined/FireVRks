#include "UI/lib/Container/DFUIContainer.h"

#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"

UPanelSlot* UDFUIContainer::Append(UWidget* Widget)
{
	return GetMountingPoint()->AddChild(Widget);
}

