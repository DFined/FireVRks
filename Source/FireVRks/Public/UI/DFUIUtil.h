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
	static T* AddWidget(UWidgetTree* Tree, UPanelWidget* Parent);

	template <class T>
	static T* AddWidget(UDFUIContainer* Container);

	template <class T>
	static T* MakeWidget(UWidgetTree* Tree);

	template <class T>
	static T* MakeWidget(UDFUIContainer* Container);

	/**
	* Util compact UserWidget constructors
	*/
	template <class T>
	static T* AddUserWidget(UPanelWidget* Parent);

	template<class T>
	static T* AttemptFindWidgetByType(UWidget* Widget);
	
	template<class T>
	static T* AttemptFindWidgetByOuterChain(UWidget* Widget);
	
	template<class T>
	static T* AttemptFindWidgetByParentChain(UWidget* Widget);
	
	static UWidgetTree* AttemptFindWidgetTree(UWidget* Widget);

	template <class T>
	static T* AddUserWidget(UDFUIContainer* Parent);

	template <class T, class P>
	static T* MakeUserWidget(P* Outer);

	/**
	 * Wrap the first widget in the second one
	 */
	template <class T>
	static T* Wrap(T* Content, UPanelWidget* Wrapper);

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

	static UExpandableArea* MakeExpandableTab(UWidgetTree* Tree, UPanelWidget* Parent, UWidget* Header, UWidget* Body, bool Expanded);
	
	static UButton* MakeImageButton(UWidgetTree* Tree, UPanelWidget* Parent, Icon* Icon, int Size)
	{
		auto Button = AddWidget<UButton>(Tree, Parent);
		DFStyleUtil::ImgButtonStyle(Button, Icon, Size);
		
		return Button;
	}
};
