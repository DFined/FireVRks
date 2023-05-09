#include "DFUIUtil.h"
#include "assert.h"

template <class T>
T* DFUIUtil::MakeWidget(UWidgetTree* Tree)
{
	assert(!T::StaticClass()->IsChildOf(UUserWidget::StaticClass()));
	return Tree->ConstructWidget<T>(T::StaticClass());
}

template <class T>
T* DFUIUtil::MakeWidget(UDFUIContainer* Container)
{
	assert(!T::StaticClass()->IsChildOf(UUserWidget::StaticClass()));
	return Container->WidgetTree->ConstructWidget<T>(T::StaticClass());
}

template <class T>
T* DFUIUtil::AddUserWidget(UPanelWidget* Parent)
{
	auto Widget = MakeUserWidget<T, UPanelWidget>(Parent);
	Parent->AddChild(Widget);
	return Widget;
}

template <class T>
T* DFUIUtil::AddUserWidget(UDFUIContainer* Parent)
{
	auto Widget = MakeUserWidget<T, UDFUIContainer>(Parent);
	Parent->Append(Widget);
	return Widget;
}

template <class T, class P>
T* DFUIUtil::MakeUserWidget(P* Outer)
{
	assert(T::StaticClass()->IsChildOf(UUserWidget::StaticClass()));
	auto Widget = CreateWidget<T, P*>(Outer, T::StaticClass());
	Widget->BaseInit();
	return Widget;
}

template <class T>
T* DFUIUtil::Wrap(T* Content, UPanelWidget* Wrapper)
{
	Wrapper->AddChild(Content);
	return Content;
}

template <class T>
T* DFUIUtil::AddWidget(UDFUIContainer* Container)
{
	auto Widget = MakeWidget<T>(Container->WidgetTree);
	Container->Append(Widget);
	return Widget;
}

template <class T>
T* DFUIUtil::AddWidget(UWidgetTree* Tree, UPanelWidget* Parent)
{
	auto Widget = MakeWidget<T>(Tree);
	Parent->AddChild(Widget);
	return Widget;
}


UExpandableArea* DFUIUtil::MakeExpandableTab(UWidgetTree* Tree, UPanelWidget* Parent, UWidget* Header, UWidget* Body, bool Expanded)
{
	auto Area = MakeWidget<UExpandableArea>(Tree);
	Area->SetContentForSlot("Header", Header);
	Area->SetContentForSlot("Body", Body);
	Area->SetIsExpanded(Expanded);
	Wrap(Area,Parent);
	return Area;
}
