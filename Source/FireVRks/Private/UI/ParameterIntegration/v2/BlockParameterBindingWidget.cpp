#include "UI/ParameterIntegration/v2/BlockParameterBindingWidget.h"

#include "UI/ParameterIntegration/v2/ParameterRenderer.h"
#include "Components/VerticalBoxSlot.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/BlockParameterValue.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/DFStyleUtil.h"
#include "UI/lib/Container/DFUIStack.h"

UPanelWidget* UBlockParameterBindingWidget::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	return OuterBorder;
}

UPanelWidget* UBlockParameterBindingWidget::GetMountingPoint()
{
	return OuterBorder;
}

void UBlockParameterBindingWidget::LayoutChangedTab(UExpandableArea* Area, bool bIsExpanded)
{
	Area->SetIsExpanded(bIsExpanded);
	this->ForceLayoutPrepass();
	LayoutChanged();
}

void UBlockParameterBindingWidget::Initialize(UAbstractFormalParameter* Param, UParameterValueContext* Context)
{

	UBlockFormalParameter* ParamsBlock = Cast<UBlockFormalParameter>(Parameter);

	auto State = Cast<UBlockParameterValue>(Context->Get(Parameter));


	DFStyleUtil::SetPadding<UVerticalBoxSlot>(OuterBorder, FMargin(10, 0, 0, 0));
	DFStyleUtil::BasicBorderStyle(OuterBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_1);

	HeaderBox = UDFUIUtil::MakeWidget<UHorizontalBox>(WidgetTree);
	auto BlockName = UDFUIUtil::AddLabel(WidgetTree, HeaderBox, ParamsBlock->GetDisplayName());
	if(auto SlotT = Cast<UHorizontalBoxSlot>(BlockName->Slot))
	{
		SlotT->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}
	DFStyleUtil::TextBlockStyle(BlockName);

	UVerticalBox* ListWrapper = UDFUIUtil::MakeWidget<UVerticalBox>(WidgetTree);

	BaseTab = UDFUIUtil::MakeExpandableTab(WidgetTree, OuterBorder, HeaderBox, ListWrapper, State->IsExpanded());
	BaseTab->OnExpansionChanged.AddUniqueDynamic(this, &UBlockParameterBindingWidget::LayoutChangedTab);

	RequiredParamsStack = UDFUIUtil::AddUserWidget<UDFUIStack>(ListWrapper);
	
	DFStyleUtil::SetPadding<UVerticalBoxSlot>(RequiredParamsStack, FMargin(6, 0, 0, 0));

	auto OverridesBorder = UDFUIUtil::AddWidget<UBorder>(WidgetTree, ListWrapper);

	DFStyleUtil::BasicBorderStyle(OverridesBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_1);

	OverrideParamsStack = UDFUIUtil::MakeUserWidget<UDFUIStack>(OverridesBorder);

	for (UAbstractFormalParameter* ChildParam : ParamsBlock->GetChildParameters())
	{
		if (ChildParam->GetPredicate()->Check(Context))
		{
			UDFUIContainer* Container = ChildParam->IsRequired() ? RequiredParamsStack : OverrideParamsStack;
			auto ChildWidget = UParameterRenderer::RenderParam(Container, Context, ChildParam);
			ChildWidget->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UBlockParameterBindingWidget::LayoutChanged);
		}
	}
	auto OverridesLabel = UDFUIUtil::MakeLabel(WidgetTree, "Overrides");
	DFStyleUtil::TextBlockStyle(OverridesLabel);
	OverridesTab = UDFUIUtil::MakeExpandableTab(
		WidgetTree, OverridesBorder, OverridesLabel, OverrideParamsStack, State->IsOverridesExpanded()
	);
	OverridesTab->OnExpansionChanged.AddUniqueDynamic(this, &UBlockParameterBindingWidget::LayoutChangedTab);
	
	if (!OverrideParamsStack->GetMountingPoint()->HasAnyChildren())
	{
		OverridesTab->SetVisibility(ESlateVisibility::Collapsed);
	}

	OverridesTab->BorderBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
}

void UBlockParameterBindingWidget::WriteToContext(UParameterValueContext* Context)
{
	auto Val = UBlockParameterValue::New(Context, BaseTab->GetIsExpanded(), OverridesTab->GetIsExpanded());
	Context->SetValue(Parameter, Val);
	UParamUtil::WriteContainerToContext(RequiredParamsStack->GetMountingPoint(), Context);
	UParamUtil::WriteContainerToContext(OverrideParamsStack->GetMountingPoint(), Context);
}
