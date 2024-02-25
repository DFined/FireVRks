// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/SystemInstantiationParameterBindingWidget.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParameterValue/SystemInstantiationParameterValue.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "DFUI/DFUI.h"
#include "UI/ParameterIntegration/v2/EffectParameterInputUI.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"
#include "Util/DFStatics.h"

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

void USystemInstantiationParameterBindingWidget::InitializeBindingWidget()
{
	auto Value = Cast<USystemInstantiationParameterValue>(Context->Get(Parameter));
	System = UEffectSystemManager::GetInstance()->Get(Value->GetSystem());

	//Kind of a hack, but when in binding mode, we need to replace the default value with a custom default
	//complete with a binding context, as well as adding it to constants straight away
	if (DrawType == INNER_SYSTEM_BINDING && !Cast<UBindingParameterValueContext>(Value->GetContext()))
	{
		auto SubContext = UBindingParameterValueContext::New(Context);
		SubContext->SetOuterContext(UMapParameterValueContext::Instance(SubContext));
		SubContext->SetBindings(USubsystemParameterBindings::Instance(SubContext));
		Value = USystemInstantiationParameterValue::New(Context, SubContext, System->GetId());
		if (auto BindingContext = Cast<UBindingParameterValueContext>(Context))
		{
			BindingContext->GetBindings()->GetConstantValues().Add(Parameter->GetId(), Value);
		}
	}


	auto VBox = DFUI::AddWidget<UVerticalBox>(OuterBorder);
	auto Box = DFUI::AddWidget<UHorizontalBox>(VBox);

	auto ParamName = DFUI::AddLabel(Box, Parameter->GetDisplayName());
	DFStyleUtil::SafeSetHBoxSlotWidth(ParamName->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	auto SysSelector = DFUI::AddWidget<USystemDisplayTile>(Box);
	DFStyleUtil::SafeSetHBoxSlotWidth(SysSelector->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	SysSelector->SetSystem(System, 96);

	InstanceParamUI = DFUI::AddWidget<UEffectParameterInputUI>(VBox);
	InstanceParamUI->SetSystem(System);
	InstanceParamUI->Draw(Value->GetContext(), DrawType);
	InstanceParamUI->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &USystemInstantiationParameterBindingWidget::LayoutChanged);
}

void USystemInstantiationParameterBindingWidget::WriteToContext(UParameterValueContext* bContext)
{
	auto InstanceContext = NewObject<UMapParameterValueContext>(bContext, UMapParameterValueContext::StaticClass());
	InstanceParamUI->WriteToContext(InstanceContext);
	auto Val = USystemInstantiationParameterValue::New(bContext, InstanceContext, System->GetId());
	bContext->SetValue(Parameter, Val);
}
