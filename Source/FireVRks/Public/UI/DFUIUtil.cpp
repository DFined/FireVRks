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
	auto ParentWidgetTree = AttemptFindWidgetTree(Parent);
	auto Widget = MakeUserWidget<T, UWidgetTree>(ParentWidgetTree);
	Parent->AddChild(Widget);
	return Widget;
}

template <class T>
T* DFUIUtil::AttemptFindWidgetByType(UWidget* Widget)
{
	auto OuterRes = AttemptFindWidgetByOuterChain<T>(Widget);
	if (OuterRes)
	{
		return OuterRes;
	}
	return AttemptFindWidgetByParentChain<T>(Widget);
}

template <class T>
T* DFUIUtil::AttemptFindWidgetByOuterChain(UWidget* Widget)
{
	if (auto SelfAsTarget = Cast<T>(Widget))
	{
		return SelfAsTarget;
	}
	auto Outer = Widget->GetOuter();
	auto OuterAsWidget = Cast<UWidget>(Outer);
	auto OuterAsTarget = Cast<T>(Outer);
	if (OuterAsTarget)
	{
		return OuterAsTarget;
	}
	if (OuterAsWidget)
	{
		AttemptFindWidgetTree(OuterAsWidget);
	}
	return nullptr;
}

template <class T>
T* DFUIUtil::AttemptFindWidgetByParentChain(UWidget* Widget)
{
	if (auto SelfAsTarget = Cast<T>(Widget))
	{
		return SelfAsTarget;
	}
	auto Parent = Widget->GetParent();
	auto ParentAsWidget = Cast<UWidget>(Parent);
	auto ParentAsTarget = Cast<T>(Parent);
	if (ParentAsTarget)
	{
		return ParentAsTarget;
	}
	if (ParentAsWidget)
	{
		AttemptFindWidgetTree(ParentAsWidget);
	}
	return nullptr;
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


UWidgetTree* DFUIUtil::AttemptFindWidgetTree(UWidget* Widget)
{
	auto Outer = Widget->GetOuter();
	auto AutoWidget = Cast<UWidget>(Outer);
	auto AutoUserWidget = Cast<UUserWidget>(Outer);
	auto WidgetTree = Cast<UWidgetTree>(Outer);
	if (WidgetTree)
	{
		return WidgetTree;
	}
	if (AutoUserWidget)
	{
		return AutoUserWidget->WidgetTree;
	}
	if (AutoWidget)
	{
		AttemptFindWidgetTree(AutoWidget);
	}
	return nullptr;
}

UExpandableArea* DFUIUtil::MakeExpandableTab(UWidgetTree* Tree, UPanelWidget* Parent, UWidget* Header, UWidget* Body, bool Expanded)
{
	auto Area = MakeWidget<UExpandableArea>(Tree);
	Area->SetContentForSlot("Header", Header);
	Area->SetContentForSlot("Body", Body);
	Area->SetIsExpanded(Expanded);
	Wrap(Area, Parent);
	return Area;
}
