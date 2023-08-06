#include "UI/ParameterIntegration/ParameterBindingList.h"

#include "UI/ParameterIntegration/ParameterBindingBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBoxSlot.h"
#include "FX/Niagara/SystemSettings/FormalParameter/ListFormalParameter.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/Container/DFUIStack.h"

UParameterBindingBlock* UParameterBindingList::AddWidgetFromParam(ParameterValueContext* PVC, BlockCompoundParameter* Param)
{
	auto Block = DFUIUtil::AddUserWidget<UParameterBindingBlock>(ListStack);
	Block->Initialize(PVC, Param);
	return Block;
}

UPanelWidget* UParameterBindingList::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_0);
	return OuterBorder;
}

void UParameterBindingList::Initialize(ParameterValueContext* ValueContext, AbstractFormalParameter* Param)
{
	ParameterBindingWidget::Initialize(ValueContext, Param);
	auto OuterVBox = DFUIUtil::AddWidget<UVerticalBox>(this->WidgetTree, OuterBorder);
	auto HeaderBox = DFUIUtil::AddUserWidget<UDFUILine>(OuterVBox);
	auto NameLabel = DFUIUtil::AddLabel(this->WidgetTree, HeaderBox->GetMountingPoint(), Parameter->GetName());
	DFStyleUtil::TextBlockStyle(NameLabel);
	if(UHorizontalBoxSlot* TSlot = Cast<UHorizontalBoxSlot>(NameLabel->Slot))
	{
		TSlot->SetPadding(FMargin(0,0,30,0));
		TSlot->SetVerticalAlignment(VAlign_Center);
	}
	auto Button = DFUIUtil::AddWidget<UButton>(HeaderBox);
	auto MKNewLabel = DFUIUtil::AddLabel(WidgetTree, Button, "Create new");
	DFStyleUtil::TextButtonStyle(Button, DFStyleUtil::GREY_LVL_2);
	Button->OnPressed.AddUniqueDynamic(this, &UParameterBindingList::NewItem);

	ListStack = DFUIUtil::AddUserWidget<UDFUIStack>(OuterVBox);


	auto Vals = static_cast<ListParameterValue*>(ValueContext->Get(Param));
	auto ListParam = static_cast<ListFormalParameter*>(Param);
	for (ParameterValueContext* SubContext : Vals->GetValues())
	{
		AddWidgetFromParam(SubContext, ListParam->GetChildType())->MakeListItem(this);
	}
}

void UParameterBindingList::SetValueInContext(MapParameterValueContext* Context)
{
	auto Value = new ListParameterValue(false);
	for(UWidget* Widget: ListStack->GetMountingPoint()->GetAllChildren())
	{
		if(auto ParamWidget = Cast<UDFUIParameterBindingWidgetBase>(Widget))
		{
			MapParameterValueContext* NewContext = new MapParameterValueContext(false);
			Value->AddValue(NewContext);
			ParamWidget->SetValueInContext(NewContext);
		}
	}
	Context->SetValue(this->GetParameter()->GetGUID(), Value);
}

void UParameterBindingList::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	Callbacks.Add(Callback);
	for (UWidget* Widget : ListStack->GetMountingPoint()->GetAllChildren())
	{
		if (ParameterBindingWidget* PBW = Cast<UDFUIParameterBindingWidgetBase>(Widget))
		{
			PBW->SubscribeToChanges(Callback);
		}
	}
}

void UParameterBindingList::RemoveItem(UDFUIParameterBindingWidgetBase* Widget)
{
	ListStack->GetMountingPoint()->RemoveChild(Widget);
	OnChange();
}


void UParameterBindingList::NewItem()
{
	ParameterValueContext* NewContext = new MapParameterValueContext(false);
	auto ListParam = static_cast<ListFormalParameter*>(Parameter);
	AddWidgetFromParam(NewContext, ListParam->GetChildType());
	OnChange();
}

UParameterBindingList::~UParameterBindingList()
{
}

void UParameterBindingList::CleanUp()
{
	Super::CleanUp();
	OuterBorder->RemoveFromParent();
	for (UWidget* AllChild : ListStack->GetMountingPoint()->GetAllChildren())
	{
		auto Child = static_cast<UDFUIParameterBindingWidgetBase*>(AllChild);
		Child->CleanUp();
		Child->RemoveFromParent();
	}
}
