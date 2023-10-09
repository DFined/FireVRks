#include "BlockParameterBindingWidget.h"

#include "ParameterRenderer.h"
#include "Components/VerticalBoxSlot.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/BlockParameterValue.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/DFStyleUtil.h"
#include "UI/lib/Container/DFUIStack.h"

UPanelWidget* UBlockParameterBindingWidget::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	return OuterBorder;
}

UPanelWidget* UBlockParameterBindingWidget::GetMountingPoint()
{
	return OuterBorder;
}

void UBlockParameterBindingWidget::Initialize(UAbstractFormalParameter* Param, UParameterValueContext* Context)
{

	UBlockFormalParameter* ParamsBlock = Cast<UBlockFormalParameter>(Parameter);

	auto State = Cast<UBlockParameterValue>(Context->Get(Parameter));


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

	BaseTab = DFUIUtil::MakeExpandableTab(WidgetTree, OuterBorder, HeaderBox, ListWrapper, State->IsExpanded());

	RequiredParamsStack = DFUIUtil::AddUserWidget<UDFUIStack>(ListWrapper);
	
	DFStyleUtil::SetPadding<UVerticalBoxSlot>(RequiredParamsStack, FMargin(6, 0, 0, 0));

	auto OverridesBorder = DFUIUtil::AddWidget<UBorder>(WidgetTree, ListWrapper);

	DFStyleUtil::BasicBorderStyle(OverridesBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_1);

	OverrideParamsStack = DFUIUtil::MakeUserWidget<UDFUIStack>(OverridesBorder);

	for (UAbstractFormalParameter* ChildParam : ParamsBlock->GetChildParameters())
	{
		if (ChildParam->GetPredicate()->Check(Context))
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

void UBlockParameterBindingWidget::WriteToContext(UParameterValueContext* Context)
{
	UParamUtil::WriteContainerToContext(RequiredParamsStack->GetMountingPoint(), Context);
	UParamUtil::WriteContainerToContext(OverrideParamsStack->GetMountingPoint(), Context);
}
