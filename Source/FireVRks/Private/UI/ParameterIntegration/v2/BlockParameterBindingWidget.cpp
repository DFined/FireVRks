#include "UI/ParameterIntegration/v2/BlockParameterBindingWidget.h"

#include "UI/ParameterIntegration/v2/ParameterRenderer.h"
#include "Components/VerticalBoxSlot.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/BlockParameterValue.h"
#include "DFUI/DFUI.h"
#include "DFUI/DFStyleUtil.h"
#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "UI/lib/Container/DFUIStack.h"

UPanelWidget* UBlockParameterBindingWidget::MakeRootWidget()
{
	OuterBorder = DFUI::MakeWidget<UBorder>(this);
	return OuterBorder;
}

UPanelWidget* UBlockParameterBindingWidget::GetMountingPoint()
{
	return OuterBorder;
}

void UBlockParameterBindingWidget::LayoutChangedTab(UExpandableArea* Area, bool bIsExpanded)
{
	Area->SetIsExpanded(bIsExpanded);
	auto BlockVal = Cast<UBlockParameterValue>(Context->Get(Parameter));
	BlockVal->SetExpanded(BaseTab->GetIsExpanded());
	Context->SetValue(Parameter, BlockVal);
	BlockVal->SetOverridesExpanded(OverridesTab->GetIsExpanded());
	this->ForceLayoutPrepass();
	LayoutChanged();
}

void UBlockParameterBindingWidget::InitializeBindingWidget()
{
	UBlockFormalParameter* ParamsBlock = Cast<UBlockFormalParameter>(Parameter);

	auto State = Cast<UBlockParameterValue>(Context->Get(Parameter));


	DFStyleUtil::SetPadding<UVerticalBoxSlot>(OuterBorder, FMargin(10, 0, 0, 0));
	DFStyleUtil::BasicBorderStyle(OuterBorder, DFStyleUtil::GREY_LVL_1);

	HeaderBox = DFUI::MakeWidget<UHorizontalBox>(this);
	auto BlockName = DFUI::AddLabel(HeaderBox, ParamsBlock->GetDisplayName());
	if (auto SlotT = Cast<UHorizontalBoxSlot>(BlockName->Slot))
	{
		SlotT->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}

	UVerticalBox* ListWrapper = DFUI::MakeWidget<UVerticalBox>(this);

	BaseTab = DFUI::MakeExpandableTab(OuterBorder, HeaderBox, ListWrapper, State->IsExpanded());
	BaseTab->OnExpansionChanged.AddUniqueDynamic(this, &UBlockParameterBindingWidget::LayoutChangedTab);

	auto RequiredBox = DFUI::AddWidget<UVerticalBox>(ListWrapper);
	RequiredParamsStack = DFUI::AddWidget<UDFUIStack>(ListWrapper);

	DFStyleUtil::SetPadding<UVerticalBoxSlot>(RequiredBox, FMargin(6, 0, 0, 0));

	auto OverridesBorder = DFUI::AddWidget<UBorder>(ListWrapper);

	DFStyleUtil::BasicBorderStyle(OverridesBorder, DFStyleUtil::GREY_LVL_1);

	OverrideParamsStack = DFUI::MakeWidget<UDFUIStack>(OverridesBorder);

	for (UAbstractFormalParameter* ChildParam : ParamsBlock->GetChildParameters())
	{
		if (ChildParam->GetPredicate()->Check(Context))
		{
			UDFUIBase* Container = ChildParam->IsRequired() ? RequiredParamsStack : OverrideParamsStack;
			auto ChildWidget = UParameterRenderer::RenderParam(Container, Context, ChildParam, DrawType);
			ChildWidget->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UBlockParameterBindingWidget::LayoutChanged);
		}
	}
	auto OverridesLabel = DFUI::MakeLabel(this, "Overrides");
	OverridesTab = DFUI::MakeExpandableTab(OverridesBorder, OverridesLabel, OverrideParamsStack, State->IsOverridesExpanded());
	OverridesTab->OnExpansionChanged.AddUniqueDynamic(this, &UBlockParameterBindingWidget::LayoutChangedTab);

	if (!OverrideParamsStack->GetMountingPoint()->HasAnyChildren())
	{
		OverridesTab->SetVisibility(ESlateVisibility::Collapsed);
	}

	OverridesTab->BorderBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
}

void UBlockParameterBindingWidget::WriteToContext(UParameterValueContext* bContext)
{
	auto Val = UBlockParameterValue::New(bContext, BaseTab->GetIsExpanded(), OverridesTab->GetIsExpanded());
	bContext->SetValue(Parameter, Val);
	UParamUtil::WriteContainerToContext(RequiredParamsStack->GetMountingPoint(), bContext);
	UParamUtil::WriteContainerToContext(OverrideParamsStack->GetMountingPoint(), bContext);
}

void UBlockParameterBindingWidget::RedrawParameters(bool Required)
{
	UBlockFormalParameter* BlockParameter = Cast<UBlockFormalParameter>(Parameter);
	UDFUIBase* Stack = Required ? RequiredParamsStack : OverrideParamsStack;
	TArray<UWidget*> ChildWidgets = TArray<UWidget*>();
	TArray<UWidget*> WidgetsToDelete = TArray<UWidget*>();
	auto Children = Stack->GetMountingPoint()->GetAllChildren();
	Stack->GetMountingPoint()->ClearChildren();
	for (UAbstractFormalParameter* ChildParameter : BlockParameter->GetChildParameters())
	{
		if (ChildParameter->IsRequired() == Required)
		{
			bool ShouldBeVisible = ChildParameter->GetPredicate()->Check(Context);
			
			if(ShouldBeVisible)
			{
				UParameterRenderer::RenderParam(Stack, Context, ChildParameter, DrawType);
			}
		}
	}
	auto Value = Cast<UBlockParameterValue>(Context->Get(Parameter));
	this->BaseTab->SetIsExpanded(Value->IsExpanded());
	this->OverridesTab->SetIsExpanded(Value->IsOverridesExpanded());
}

void UBlockParameterBindingWidget::Redraw()
{
	RedrawParameters(true);
	RedrawParameters(false);
}
