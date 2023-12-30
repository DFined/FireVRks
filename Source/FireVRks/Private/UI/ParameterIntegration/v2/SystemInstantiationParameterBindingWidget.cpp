// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/SystemInstantiationParameterBindingWidget.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/SystemInstantiationParameterValue.h"
#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/EffectParameterInputUI.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"
#include "Util/DFStatics.h"

UPanelWidget* USystemInstantiationParameterBindingWidget::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, DFStyleUtil::GREY_LVL_1);
	return OuterBorder;
}

UPanelWidget* USystemInstantiationParameterBindingWidget::GetMountingPoint()
{
	return OuterBorder;
}

void USystemInstantiationParameterBindingWidget::InitializeBindingWidget()
{
	auto Value = Cast<USystemInstantiationParameterValue>(Context->Get(Parameter));
	System = UDFStatics::EFFECT_SYSTEM_MANAGER->Get(Value->GetSystem());

	auto VBox = UDFUIUtil::AddWidget<UVerticalBox>(WidgetTree, OuterBorder);
	auto Box = UDFUIUtil::AddWidget<UHorizontalBox>(WidgetTree, VBox);

	auto ParamName = UDFUIUtil::AddLabel(WidgetTree, Box, Parameter->GetDisplayName());
	DFStyleUtil::SafeSetHBoxSlotWidth(ParamName->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	DFStyleUtil::TextBlockStyle(ParamName);

	auto SysSelector = UDFUIUtil::AddUserWidget<USystemDisplayTile>(Box);
	DFStyleUtil::SafeSetHBoxSlotWidth(SysSelector->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	SysSelector->SetSystem(System, 96);

	InstanceParamUI = UDFUIUtil::AddWidget<UEffectParameterInputUI>(WidgetTree, VBox);
	InstanceParamUI->SetSystem(System);
	InstanceParamUI->Draw(Value->GetContext());
	InstanceParamUI->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &USystemInstantiationParameterBindingWidget::LayoutChanged);
}

void USystemInstantiationParameterBindingWidget::WriteToContext(UParameterValueContext* bContext)
{
	auto InstanceContext = NewObject<UMapParameterValueContext>(bContext, UMapParameterValueContext::StaticClass());
	InstanceParamUI->WriteToContext(InstanceContext);
	auto Val = USystemInstantiationParameterValue::New(bContext, InstanceContext, System->GetId());
	bContext->SetValue(Parameter, Val);
}
