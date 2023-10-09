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
	OuterBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_1);
	return OuterBorder;
}

UPanelWidget* USystemInstantiationParameterBindingWidget::GetMountingPoint()
{
	return OuterBorder;
}

void USystemInstantiationParameterBindingWidget::Initialize(UAbstractFormalParameter* fParameter, UParameterValueContext* Context)
{
	auto Value = Cast<USystemInstantiationParameterValue>(Context->Get(fParameter));
	System = UDFStatics::EFFECT_SYSTEM_MANAGER->Get(Value->GetSystem());

	auto VBox = DFUIUtil::AddWidget<UVerticalBox>(WidgetTree, OuterBorder);
	auto Box = DFUIUtil::AddWidget<UHorizontalBox>(WidgetTree, VBox);

	auto ParamName = DFUIUtil::AddLabel(WidgetTree, Box, fParameter->GetName());
	DFStyleUtil::SafeSetHBoxSlotWidth(ParamName->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	DFStyleUtil::TextBlockStyle(ParamName);

	auto SysSelector = DFUIUtil::AddUserWidget<USystemDisplayTile>(Box);
	DFStyleUtil::SafeSetHBoxSlotWidth(SysSelector->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	SysSelector->SetSystem(System, 96);

	InstanceParamUI = DFUIUtil::AddWidget<UEffectParameterInputUI>(WidgetTree, VBox);
	InstanceParamUI->SetSystem(System);
	InstanceParamUI->Draw(Value->GetContext());
}

void USystemInstantiationParameterBindingWidget::WriteToContext(UParameterValueContext* Context)
{
	auto InstanceContext = NewObject<UMapParameterValueContext>(Context, UMapParameterValueContext::StaticClass());
	InstanceParamUI->WriteToContext(InstanceContext);
	auto Val = USystemInstantiationParameterValue::New(Context, InstanceContext, System->GetId());
	Context->SetValue(Parameter, Val);
}
