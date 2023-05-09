#include "UI/lib/Container/DFUIContainer.h"

#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"

void UDFUIContainer::RebuildWidgetInternal()
{
	GetOrCreateRoot();
}

UPanelSlot* UDFUIContainer::Append(UWidget* Widget)
{
	return GetMountingPoint()->AddChild(Widget);
}

void UDFUIContainer::BaseInit()
{
	GetOrCreateRoot();
}
