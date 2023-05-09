#include "UI/ParameterIntegration/ParameterBindingBlock.h"

#include "UI/ParameterIntegration/ParameterRenderer.h"
#include "Components/Border.h"
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/Container/DFUIStack.h"
#include "Unsafe/ParameterIntegration/DFParameterUtil.h"

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

	auto BlockName = DFUIUtil::MakeLabel(WidgetTree, ParamsBlock->GetName());
	DFStyleUtil::TextBlockStyle(BlockName);

	UVerticalBox* ListWrapper = DFUIUtil::MakeWidget<UVerticalBox>(WidgetTree);

	BaseTab = DFUIUtil::MakeExpandableTab(WidgetTree, OuterBorder, BlockName, ListWrapper, State->IsBlockExpanded());

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
