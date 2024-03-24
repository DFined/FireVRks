// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/SystemInstantiationParameterBindingWidget.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/SystemInstantiationParameterValue.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "DFUI/DFUI.h"
#include "UI/ParameterIntegration/v2/EffectParameterInputUI.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"

UPanelWidget* USystemInstantiationParameterBindingWidget::MakeRootWidget()
{
	OuterBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(OuterBorder, DFStyleUtil::GREY_LVL_1);
	return OuterBorder;
}

UPanelWidget* USystemInstantiationParameterBindingWidget::GetMountingPoint()
{
	return OuterBorder;
}

void USystemInstantiationParameterBindingWidget::SetupSystem(UEffectSystem* bSystem)
{
	auto Value = Cast<USystemInstantiationParameterValue>(Context->Get(Parameter));
	Value->SetSystem(bSystem->GetId());
	
	this->System = bSystem;
	OuterBorder->ClearChildren();
	auto VBox = DFUI::AddWidget<UVerticalBox>(OuterBorder);
	auto Box = DFUI::AddWidget<UHorizontalBox>(VBox);

	auto ParamName = DFUI::AddLabel(Box, Parameter->GetDisplayName());
	DFStyleUtil::SafeSetHBoxSlotWidth(ParamName->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	auto SysSelector = DFUI::AddWidget<USystemDisplayTile>(Box);
	SysSelector->GetOnSelectionChanged().AddUniqueDynamic(this, &USystemInstantiationParameterBindingWidget::SetupSystem);
	DFStyleUtil::SafeSetHBoxSlotWidth(SysSelector->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	SysSelector->SetSystem(System);

	InstanceParamUI = DFUI::AddWidget<UEffectParameterInputUI>(VBox);
	InstanceParamUI->SetSystem(System);
	InstanceParamUI->Draw(Value->GetContext(), DrawType);
	InstanceParamUI->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &USystemInstantiationParameterBindingWidget::LayoutChanged);
}

void USystemInstantiationParameterBindingWidget::InitializeBindingWidget()
{
	auto Value = Cast<USystemInstantiationParameterValue>(Context->Get(Parameter));
	System = UEffectSystemManager::GetInstance()->Get(Value->GetSystem());

	//TODO Figure out why I thought this bit was necessary and comment the result here. Might be related to the crash on creating a new subsystem in binding mode
	// if (auto BindingContext = Cast<UBindingParameterValueContext>(Context))
	// {
	// 	BindingContext->GetBindings()->GetConstantValues().Add(Parameter->GetId(), Value);
	// }
	SetupSystem(System);
}

void USystemInstantiationParameterBindingWidget::WriteToContext(UParameterValueContext* bContext)
{
	auto InstanceContext = NewObject<UMapParameterValueContext>(bContext, UMapParameterValueContext::StaticClass());
	InstanceParamUI->WriteToContext(InstanceContext);
	auto Val = USystemInstantiationParameterValue::New(bContext, InstanceContext, System->GetId());
	bContext->SetValue(Parameter, Val);
}
