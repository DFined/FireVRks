#include "UI/lib/Container/DFUIBase.h"

#include "Blueprint/WidgetTree.h"

TSharedRef<SWidget> UDFUIBase::RebuildWidget()
{
	RebuildWidgetInternal();
	return Super::RebuildWidget();
}

UPanelWidget* UDFUIBase::GetOrCreateRoot() {

	if (WidgetTree)
	{
		if (!RootContainer)
		{
			RootContainer = this->MakeRootWidget(WidgetTree);
			WidgetTree->SetContentForSlot("Root", RootContainer);
			//For some WTF reason this actually seems to be the correct way to do this?!
			WidgetTree->RootWidget = RootContainer;
		}
		return RootContainer;
	}
	return nullptr;
}
