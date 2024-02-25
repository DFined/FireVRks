// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CoreUI/EffectEditorUI.h"

#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "FX/Niagara/v2/System/DefaultParameterSystem.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "DFUI/DFUI.h"
#include "UI/CoreUI/SystemPicker.h"
#include "UI/ParameterIntegration/v2/EffectSystemSavingWidget.h"
#include "UI/ParameterIntegration/v2/OuterParameterCreationWidget.h"
#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"

void UEffectEditorUI::OnNewSystem()
{
	auto Config = USubsystemConfig::Instance(System, UDFStatics::DEFAULT_SYSTEM_ID);
	Config->InitBindings();
	auto Subsystem = UEffectSystemManager::GetInstance()->GetDefaultEffect();
	System->GetSubsystemConfig().Add(Config);
	UParameterBindingSetupUI::InstanceFrom(SubsystemsVBox, Subsystem, Config);
}

UPanelWidget* UEffectEditorUI::MakeRootWidget()
{
	RootHBox = DFUI::MakeWidget<UHorizontalBox>(this);
	return RootHBox;
}

UPanelWidget* UEffectEditorUI::GetMountingPoint()
{
	return SubsystemsVBox;
}

void UEffectEditorUI::SetupSystem()
{
	RootHBox->ClearChildren();
	auto OuterWidget = DFUI::AddWidget<UOuterParameterCreationWidget>(RootHBox);
	OuterWidget->SetSystem(System);

	auto Size = FSlateChildSize(ESlateSizeRule::Fill);
	Size.Value = 0.8;
	DFStyleUtil::SafeSetHBoxSlotWidth(OuterWidget->Slot, Size);
	OuterWidget->Draw();

	Switcher = DFUI::AddWidget<UWidgetSwitcher>(RootHBox);
	DFStyleUtil::SafeSetHBoxSlotWidth(Switcher->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	
	Viewport = DFUI::AddWidget<UImage>(Switcher);
	Viewport->SetBrushFromAsset(UDFStatics::EFFECT_TESTING_SLATE_BRUSH);

	SavingWidget = DFUI::AddWidget<UEffectSystemSavingWidget>(Switcher);

	auto SubsystemBorder = DFUI::AddWidget<UBorder>(RootHBox);
	DFStyleUtil::BasicBorderStyle(SubsystemBorder, DFStyleUtil::GREY_LVL_2);
	auto Size2 = FSlateChildSize(ESlateSizeRule::Fill);
	Size2.Value = 0.8;
	DFStyleUtil::SafeSetHBoxSlotWidth(SubsystemBorder->Slot, Size2);

	auto ScrollBox = DFUI::AddWidget<UScrollBox>(SubsystemBorder);
	auto InnerVBox = DFUI::AddWidget<UVerticalBox>(ScrollBox);

	auto ToolBorder = DFUI::AddWidget<UBorder>(InnerVBox);
	DFStyleUtil::BasicBorderStyle(ToolBorder, DFStyleUtil::GREY_LVL_3);

	auto ToolPanel = DFUI::AddWidget<UHorizontalBox>(ToolBorder);
	auto NewSystemButton = DFUI::AddButtonToButtonPanel(ToolPanel, "Add new system");
	NewSystemButton->OnPressed.AddUniqueDynamic(this, &UEffectEditorUI::OnNewSystem);

	SubsystemsVBox = DFUI::AddWidget<UVerticalBox>(InnerVBox);

	for (USubsystemConfig* Config : System->GetSubsystemConfig())
	{
		//TODO DF_HANDLE
		auto bSystem = UEffectSystemManager::GetInstance()->Get(Config->GetId());
		UParameterBindingSetupUI::InstanceFrom(SubsystemsVBox, bSystem, Config);
	}
}

void UEffectEditorUI::Init(UTextureRenderTarget2D* RenderTarget, UCustomEffectSystem* bSystem)
{
	MaterialInterface = RenderTarget;
	SetSystem(bSystem);
	SetupSystem();
}

void UEffectEditorUI::MoveSystemUp(UParameterBindingSetupUI* ParameterBindingSetupUI)
{
	DFUI::MoveChildUp(this->SubsystemsVBox, ParameterBindingSetupUI);
}

void UEffectEditorUI::MoveSystemDown(UParameterBindingSetupUI* ParameterBindingSetupUI)
{
	DFUI::MoveChildDown(this->SubsystemsVBox, ParameterBindingSetupUI);
}

UEffectEditorUI* UEffectEditorUI::Instance(UPanelWidget* Parent, UTextureRenderTarget2D* MaterialForViewport)
{
	auto UI = DFUI::AddWidget<UEffectEditorUI>(Parent);
	UI->Init(MaterialForViewport, UEffectSystemManager::GetInstance()->GetSystemInEditing());
	return UI;
}

UCustomEffectSystem* UEffectEditorUI::GetSystem() const
{
	return System;
}

void UEffectEditorUI::SaveAs()
{
	SavingWidget->SetMeta(System);
	SavingWidget->SetRenderTarget(MaterialInterface);
	Switcher->SetActiveWidget(SavingWidget);	
}

void UEffectEditorUI::LoadSystem(UEffectSystem* bSystem)
{
	if(auto CustomSystem = Cast<UCustomEffectSystem>(bSystem))
	{
		UEffectSystemManager::GetInstance()->SetSystemInEditing(CustomSystem);
		this->SetSystem(CustomSystem);
		this->SetupSystem();
	}
}

void UEffectEditorUI::BeginLoadSystem()
{
	auto Picker = USystemPicker::SelectSystem(this);
	Picker->GetOnSelectComplete().AddUniqueDynamic(this, &UEffectEditorUI::LoadSystem);
}

void UEffectEditorUI::BuildToolbar(UHorizontalBox* Parent)
{
	LoadButton = DFUI::AddButtonToButtonPanel(Parent, "Load");
	SaveButton = DFUI::AddButtonToButtonPanel(Parent, "Save");
	SaveAsButton = DFUI::AddButtonToButtonPanel(Parent, "Save as");

	SaveAsButton->OnPressed.AddUniqueDynamic(this, &UEffectEditorUI::SaveAs);
	LoadButton->OnPressed.AddUniqueDynamic(this, &UEffectEditorUI::BeginLoadSystem);
}

void UEffectEditorUI::SetSystem(UCustomEffectSystem* bSystem)
{
	this->System = bSystem;
}
