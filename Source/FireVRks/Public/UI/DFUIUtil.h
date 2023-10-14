#pragma once
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ExpandableArea.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "lib/Container/DFUILine.h"
#include "UI/lib/DFStyleUtil.h"

#define NDEBUG 1

class DFUIUtil
{
public:
	/**
	 * Util compact widget constructors
	 */
	template <class T>
	static T* MakeWidget(UWidgetTree* Tree)
	{
		return Tree->ConstructWidget<T>(T::StaticClass());
	}

	template <class T>
	static T* MakeWidget(UDFUIContainer* Container)
	{
		return Container->WidgetTree->ConstructWidget<T>(T::StaticClass());
	}

	template <class T>
	static T* AddUserWidget(UPanelWidget* Parent)
	{
		auto ParentWidgetTree = AttemptFindWidgetTree(Parent);
		auto Widget = MakeUserWidget<T, UWidgetTree>(ParentWidgetTree);
		Parent->AddChild(Widget);
		return Widget;
	}

	template <class T>
	static T* AttemptFindWidgetByType(UWidget* Widget)
	{
		if (auto UserWidget = FindOuterParent(Widget))
		{
			if(auto OuterAsTarget = Cast<T>(UserWidget))
			{
				return OuterAsTarget;
			} 
			return AttemptFindWidgetByType<T>(UserWidget);
		}
		return nullptr;
	}

	template <class T>
	static T* AttemptFindWidgetByOuterChain(UWidget* Widget)
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

	static UUserWidget* FindOuterParent(UWidget* Widget)
	{
		auto Parent = Widget->GetParent();
		if (Parent == nullptr)
		{
			if (auto Outer = Cast<UWidgetTree>(Widget->GetOuter()))
			{
				if (auto ParentUWidget = Cast<UUserWidget>(Outer->GetOuter()))
				{
					return ParentUWidget;
				}
			}
		}
		if(auto ParentAsWidget = Cast<UWidget>(Parent))
		{
			return FindOuterParent(ParentAsWidget);			
		}
		return nullptr;
	}


	template <class T>
	static T* AddUserWidget(UDFUIContainer* Parent)
	{
		auto Widget = MakeUserWidget<T, UDFUIContainer>(Parent);
		Parent->Append(Widget);
		return Widget;
	}

	template <class T, class P>
	static T* MakeUserWidget(P* Outer)
	{
		auto Widget = CreateWidget<T, P*>(Outer, T::StaticClass());
		Widget->BaseInit();
		return Widget;
	}

	template <class T>
	static T* Wrap(T* Content, UPanelWidget* Wrapper)
	{
		Wrapper->AddChild(Content);
		return Content;
	}

	template <class T>
	static T* AddWidget(UDFUIContainer* Container)
	{
		auto Widget = MakeWidget<T>(Container->WidgetTree);
		Container->Append(Widget);
		return Widget;
	}

	template <class T>
	static T* AddWidget(UWidgetTree* Tree, UPanelWidget* Parent)
	{
		auto Widget = MakeWidget<T>(Tree);
		Parent->AddChild(Widget);
		return Widget;
	}


	static UWidgetTree* AttemptFindWidgetTree(UWidget* Widget)
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

	static UExpandableArea* MakeExpandableTab(UWidgetTree* Tree, UPanelWidget* Parent, UWidget* Header, UWidget* Body, bool Expanded)
	{
		auto Area = MakeWidget<UExpandableArea>(Tree);
		Area->SetContentForSlot("Header", Header);
		Area->SetContentForSlot("Body", Body);
		Area->SetIsExpanded(Expanded);
		Wrap(Area, Parent);
		return Area;
	}


	/**
	 * Wrap the first widget in the second one
	 */
	static UTextBlock* AddLabel(UWidgetTree* Tree, UPanelWidget* Outer, FString Name)
	{
		auto NameBox = MakeLabel(Tree, Name);
		Outer->AddChild(NameBox);
		return NameBox;
	}

	static UTextBlock* MakeLabel(UWidgetTree* Tree, FString Name)
	{
		auto NameBox = Tree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		NameBox->SetText(FText::FromString(Name));
		return NameBox;
	}


	static UEditableTextBox* TextInput(UDFUIContainer* Widget)
	{
		UEditableTextBox* TextBox = Widget->WidgetTree->ConstructWidget<UEditableTextBox>(UEditableTextBox::StaticClass());
		Widget->GetMountingPoint()->AddChild(TextBox);
		return TextBox;
	}

	static UEditableTextBox* TextInput(UPanelWidget* Widget, UWidgetTree* Tree)
	{
		UEditableTextBox* TextBox = Tree->ConstructWidget<UEditableTextBox>(UEditableTextBox::StaticClass());
		Widget->AddChild(TextBox);
		return TextBox;
	}

	static UButton* MakeImageButton(UWidgetTree* Tree, UPanelWidget* Parent, Icon* Icon, int Size)
	{
		auto Button = AddWidget<UButton>(Tree, Parent);
		DFStyleUtil::ImgButtonStyle(Button, Icon, Size);

		return Button;
	}
};
