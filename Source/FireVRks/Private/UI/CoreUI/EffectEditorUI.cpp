// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoreUI/EffectEditorUI.h"

#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/OuterParameterCreationWidget.h"
#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"

UPanelWidget* UEffectEditorUI::MakeRootWidget(UWidgetTree* Tree)
{
	RootHBox = UDFUIUtil::MakeWidget<UHorizontalBox>(Tree);

	this->Context = UBindingParameterValueContext::New(this);

	auto OuterWidget = UDFUIUtil::AddWidget<UOuterParameterCreationWidget>(Tree, RootHBox);
	auto Size = FSlateChildSize(ESlateSizeRule::Fill);
	Size.Value = 0.8;
	DFStyleUtil::SafeSetHBoxSlotWidth(OuterWidget->Slot, Size);
	OuterWidget->Draw(this->Context);
	
	auto Spacer = UDFUIUtil::AddWidget<USpacer>(Tree, RootHBox);
	DFStyleUtil::SafeSetHBoxSlotWidth(Spacer->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	
	auto InnerWidget = UParameterBindingSetupUI::InstanceFrom(RootHBox);
	auto Size2 = FSlateChildSize(ESlateSizeRule::Fill);
	Size2.Value = 0.8;
	DFStyleUtil::SafeSetHBoxSlotWidth(InnerWidget->Slot, Size2);
	
	
	return RootHBox;
}

UPanelWidget* UEffectEditorUI::GetMountingPoint()
{
	return RootHBox;
}

UEffectEditorUI* UEffectEditorUI::EmptyInstance(UPanelWidget* Parent)
{
	return UDFUIUtil::AddUserWidget<UEffectEditorUI>(Parent);
}
