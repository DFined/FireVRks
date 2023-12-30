// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CoreUI/EffectEditorUI.h"

#include "Components/ScrollBox.h"
#include "FX/Niagara/v2/System/DefaultParameterSystem.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/OuterParameterCreationWidget.h"
#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"

void UEffectEditorUI::OnNewSystem()
{
	auto Config = USubsystemConfig::Instance(System, UDFStatics::DEFAULT_SYSTEM_ID);
	Config->InitBindings();
	auto Subsystem = UDFStatics::EFFECT_SYSTEM_MANAGER->GetDefaultEffect();
	System->GetSubsystemConfig().Add(UDFId::Random(System), Config);
	UParameterBindingSetupUI::InstanceFrom(SubsystemsVBox, Subsystem, Config);
}

UPanelWidget* UEffectEditorUI::MakeRootWidget(UWidgetTree* Tree)
{
	RootHBox = UDFUIUtil::MakeWidget<UHorizontalBox>(Tree);
	return RootHBox;
}

UPanelWidget* UEffectEditorUI::GetMountingPoint()
{
	return SubsystemsVBox;
}

void UEffectEditorUI::Init()
{
	auto OuterWidget = UDFUIUtil::AddUserWidget<UOuterParameterCreationWidget>(RootHBox);
	OuterWidget->SetSystem(System);

	auto Size = FSlateChildSize(ESlateSizeRule::Fill);
	Size.Value = 0.8;
	DFStyleUtil::SafeSetHBoxSlotWidth(OuterWidget->Slot, Size);
	OuterWidget->Draw();

	auto Spacer = UDFUIUtil::AddWidget<USpacer>(WidgetTree, RootHBox);
	DFStyleUtil::SafeSetHBoxSlotWidth(Spacer->Slot, FSlateChildSize(ESlateSizeRule::Fill));

	auto SubsystemBorder = UDFUIUtil::AddWidget<UBorder>(WidgetTree, RootHBox);
	DFStyleUtil::BasicBorderStyle(SubsystemBorder, DFStyleUtil::GREY_LVL_2);
	auto Size2 = FSlateChildSize(ESlateSizeRule::Fill);
	Size2.Value = 0.8;
	DFStyleUtil::SafeSetHBoxSlotWidth(SubsystemBorder->Slot, Size2);

	auto ScrollBox = UDFUIUtil::AddWidget<UScrollBox>(WidgetTree, SubsystemBorder);
	auto InnerVBox = UDFUIUtil::AddWidget<UVerticalBox>(WidgetTree, ScrollBox);

	auto ToolBorder = UDFUIUtil::AddWidget<UBorder>(WidgetTree, InnerVBox);
	DFStyleUtil::BasicBorderStyle(ToolBorder, DFStyleUtil::GREY_LVL_3);

	auto ToolPanel = UDFUIUtil::AddWidget<UHorizontalBox>(WidgetTree, ToolBorder);
	auto NewSystemButton = UDFUIUtil::AddButtonToButtonPanel(ToolPanel, "Add new system", WidgetTree);
	NewSystemButton->OnPressed.AddUniqueDynamic(this, &UEffectEditorUI::OnNewSystem);

	SubsystemsVBox = UDFUIUtil::AddWidget<UVerticalBox>(WidgetTree, InnerVBox);
}

void UEffectEditorUI::MoveSystemUp(UParameterBindingSetupUI* ParameterBindingSetupUI)
{
	UDFUIUtil::MoveChildUp(this->SubsystemsVBox, ParameterBindingSetupUI);
}

void UEffectEditorUI::MoveSystemDown(UParameterBindingSetupUI* ParameterBindingSetupUI)
{
	UDFUIUtil::MoveChildDown(this->SubsystemsVBox, ParameterBindingSetupUI);
}

UEffectEditorUI* UEffectEditorUI::EmptyInstance(UPanelWidget* Parent)
{
	auto UI = UDFUIUtil::AddUserWidget<UEffectEditorUI>(Parent);
	UI->SetSystem(UCustomEffectSystem::Instance(UI));
	UI->Init();
	return UI;
}

UCustomEffectSystem* UEffectEditorUI::GetSystem() const
{
	return System;
}

void UEffectEditorUI::SetSystem(UCustomEffectSystem* bSystem)
{
	this->System = bSystem;
}
