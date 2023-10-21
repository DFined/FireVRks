#include "UI/lib/Container/DFUILine.h"

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "UI/DFUIUtil.h"


UPanelWidget* UDFUILine::MakeRootWidget(UWidgetTree* Tree)
{
	HBox = UDFUIUtil::MakeWidget<UHorizontalBox>(Tree);
	return HBox;
}

UPanelWidget* UDFUILine::GetMountingPoint()
{
	return HBox;
}
