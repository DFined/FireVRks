#include "UI/ParameterIntegration/ParameterBindingBlock.h"

#include "UI/ParameterIntegration/ParameterRenderer.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/HorizontalBoxSlot.h"
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/Container/DFUIStack.h"
#include "UI/ParameterIntegration/ParameterBindingList.h"
#include "Unsafe/ParameterIntegration/DFParameterUtil.h"

class UButton;

UPanelWidget* UParameterBindingBlock::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	return OuterBorder;
}

void UParameterBindingBlock::Initialize(ParameterValueContext* Context, AbstractFormalParameter* Param)
{
	ParameterBindingWidget::Initialize(Context, Param);

	BlockCompoundParameter* ParamsBlock = static_cast<BlockCompoundParameter*>(Parameter);

	auto State = static_cast<BlockUIStateParameterValue*>(Context->Get(Parameter));


	DFStyleUtil::SetPadding<UVerticalBoxSlot>(OuterBorder, FMargin(10, 0, 0, 0));
	DFStyleUtil::BasicBorderStyle(OuterBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_1);

	HeaderBox = DFUIUtil::MakeWidget<UHorizontalBox>(WidgetTree);
	auto BlockName = DFUIUtil::AddLabel(WidgetTree, HeaderBox, ParamsBlock->GetName());
	if(auto SlotT = Cast<UHorizontalBoxSlot>(BlockName->Slot))
	{
		SlotT->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}
	DFStyleUtil::TextBlockStyle(BlockName);

	UVerticalBox* ListWrapper = DFUIUtil::MakeWidget<UVerticalBox>(WidgetTree);

	BaseTab = DFUIUtil::MakeExpandableTab(WidgetTree, OuterBorder, HeaderBox, ListWrapper, State->IsBlockExpanded());

	RequiredParamsStack = DFUIUtil::AddUserWidget<UDFUIStack>(ListWrapper);
	DFStyleUtil::SetPadding<UVerticalBoxSlot>(RequiredParamsStack, FMargin(6, 0, 0, 0));

	auto OverridesBorder = DFUIUtil::AddWidget<UBorder>(WidgetTree, ListWrapper);

	DFStyleUtil::BasicBorderStyle(OverridesBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_1);

	OverrideParamsStack = DFUIUtil::MakeUserWidget<UDFUIStack>(OverridesBorder);

	for (AbstractFormalParameter* ChildParam : ParamsBlock->GetChildParameters())
	{
		if (ChildParam->GetDisplayPredicate()->Check(Context))
		{
			UDFUIContainer* Container = ChildParam->IsRequired() ? RequiredParamsStack : OverrideParamsStack;
			UParameterRenderer::RenderParam(Container, Context, ChildParam);
		}
	}
	auto OverridesLabel = DFUIUtil::MakeLabel(WidgetTree, "Overrides");
	DFStyleUtil::TextBlockStyle(OverridesLabel);
	OverridesTab = DFUIUtil::MakeExpandableTab(
		WidgetTree, OverridesBorder, OverridesLabel, OverrideParamsStack, State->IsOverridesExpanded()
	);
	
	if (!OverrideParamsStack->GetMountingPoint()->HasAnyChildren())
	{
		OverridesTab->SetVisibility(ESlateVisibility::Collapsed);
	}

	OverridesTab->BorderBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
}

void UParameterBindingBlock::SetValueInContext(MapParameterValueContext* Context)
{
	DFParameterUtil::SetContextValuesFromUI(Context, RequiredParamsStack->GetMountingPoint());
	DFParameterUtil::SetContextValuesFromUI(Context, OverrideParamsStack->GetMountingPoint());
	Context->SetValue(
		this->Parameter->GetGUID(),
		new BlockUIStateParameterValue(false, BaseTab->GetIsExpanded(), OverridesTab->GetIsExpanded())
	);
}


void UParameterBindingBlock::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	for (UWidget* Widget : RequiredParamsStack->GetMountingPoint()->GetAllChildren())
	{
		if (ParameterBindingWidget* PBW = Cast<UDFUIParameterBindingWidgetBase>(Widget))
		{
			PBW->SubscribeToChanges(Callback);
		}
	}

	for (UWidget* Widget : OverrideParamsStack->GetMountingPoint()->GetAllChildren())
	{
		if (ParameterBindingWidget* PBW = Cast<UDFUIParameterBindingWidgetBase>(Widget))
		{
			PBW->SubscribeToChanges(Callback);
		}
	}
}

void UParameterBindingBlock::MakeListItem(UParameterBindingList* PList)
{
	ParentList = PList;
	auto DeleteButton = DFUIUtil::AddWidget<UButton>(WidgetTree, HeaderBox);
	DFStyleUtil::ImgButtonStyle(DeleteButton, "DeleteButton", "/Game/FireVRks/UI/Icons/DeleteIcon.DeleteIcon", 20);
	DeleteButton->OnPressed.AddUniqueDynamic(this, &UParameterBindingBlock::OnDelete);
}

void UParameterBindingBlock::OnDelete()
{
	ParentList->RemoveItem(this);
}

void UParameterBindingBlock::CleanUp()
{
	Super::CleanUp();
	OuterBorder->RemoveFromParent();
    OverridesTab->RemoveFromParent();
    BaseTab->RemoveFromParent();
	HeaderBox->RemoveFromParent();
	ParentList = nullptr;
	
	RequiredParamsStack->CleanUpBindingWidgets();
	OverrideParamsStack->CleanUpBindingWidgets();
	
	RequiredParamsStack->RemoveFromParent();
	OverrideParamsStack->RemoveFromParent();
}
