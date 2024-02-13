#include "UI/lib/Container/DFUILine.h"

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "DFUI/DFUI.h"


UPanelWidget* UDFUILine::MakeRootWidget()
{
	HBox = DFUI::MakeWidget<UHorizontalBox>(this);
	return HBox;
}

UPanelWidget* UDFUILine::GetMountingPoint()
{
	return HBox;
}
