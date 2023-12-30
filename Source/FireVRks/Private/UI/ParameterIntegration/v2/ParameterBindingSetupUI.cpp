// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "UI/DFUIUtil.h"
#include "UI/Icons.h"
#include "UI/CoreUI/EffectEditorUI.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"

void UParameterBindingSetupUI::Delete()
{
	this->RemoveFromParent();
	auto CustomSystem = DFU::AttemptFindObjectByType<UCustomEffectSystem>(SubsystemConfig);
	CustomSystem->GetSubsystemConfig().Remove(SubsystemConfig->GetId());
}


void UParameterBindingSetupUI::MoveUp()
{
	auto Editor = UDFUIUtil::AttemptFindWidgetByType<UEffectEditorUI>(this);
	Editor->MoveSystemUp(this);
}

void UParameterBindingSetupUI::MoveDown()
{
	auto Editor = UDFUIUtil::AttemptFindWidgetByType<UEffectEditorUI>(this);
	Editor->MoveSystemDown(this);
}

UPanelWidget* UParameterBindingSetupUI::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2);

	HeaderBox = UDFUIUtil::MakeWidget<UHorizontalBox>(Tree);
	
	auto VBox = UDFUIUtil::MakeWidget<UVerticalBox>(Tree);
	
	UDFUIUtil::MakeExpandableTab(Tree, RootBorder, HeaderBox, VBox, true);

	SystemDisplayTile = UDFUIUtil::AddUserWidget<USystemDisplayTile>(VBox);

	ParamsBox = UDFUIUtil::AddWidget<UVerticalBox>(Tree, VBox);
	return RootBorder;
}


void UParameterBindingSetupUI::Setup()
{
	auto Label = UDFUIUtil::AddLabel(WidgetTree, HeaderBox, SubsystemConfig->GetSubsystemName());
	DFStyleUtil::TextBlockStyle(Label);
	DFStyleUtil::SafeSetHBoxSlotWidth(Label->Slot, FSlateChildSize(ESlateSizeRule::Automatic));

	auto Spacer = UDFUIUtil::AddWidget<USpacer>(WidgetTree, HeaderBox);
	DFStyleUtil::SafeSetHBoxSlotWidth(Spacer->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	
	auto UpBtn = UDFUIUtil::MakeImageButton(WidgetTree, HeaderBox, &Icons::UP_ICON, 24);
	DFStyleUtil::SafeSetHBoxSlotWidth(UpBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	UpBtn->OnPressed.AddUniqueDynamic(this, &UParameterBindingSetupUI::MoveUp);
	
	auto DownBtn = UDFUIUtil::MakeImageButton(WidgetTree, HeaderBox, &Icons::DOWN_ICON, 24);
	DFStyleUtil::SafeSetHBoxSlotWidth(DownBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	DownBtn->OnPressed.AddUniqueDynamic(this, &UParameterBindingSetupUI::MoveDown);

	auto DelBtn = UDFUIUtil::MakeImageButton(WidgetTree, HeaderBox, &Icons::DELETE_ICON, 24);
	DelBtn->OnPressed.AddUniqueDynamic(this, &UParameterBindingSetupUI::Delete);
	DFStyleUtil::SafeSetHBoxSlotWidth(DelBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));

	
	auto Context = UBindingParameterValueContext::New(SubsystemConfig);
	Context->SetBindings(SubsystemConfig->GetBindings());
	this->SetSystem(System);
	auto OuterParams = TArray<UAbstractFormalParameter*>();
	System->GetOuterParametersInOrder(OuterParams);
	for (auto Param : OuterParams)
	{
		UParameterRenderer::RenderParam(this, Context, Param, INNER_SYSTEM_BINDING);
	}
}

void UParameterBindingSetupUI::SetSystem(UEffectSystem* bSystem)
{
	System = bSystem;
	SystemDisplayTile->SetSystem(System, 96);
}

UPanelWidget* UParameterBindingSetupUI::GetMountingPoint()
{
	return ParamsBox;
}

UParameterBindingSetupUI* UParameterBindingSetupUI::InstanceFrom(UPanelWidget* Parent, UEffectSystem* System, USubsystemConfig* Bindings)
{
	auto SetupUI = UDFUIUtil::AddUserWidget<UParameterBindingSetupUI>(Parent);
	SetupUI->System = System;
	SetupUI->SubsystemConfig = Bindings;
	SetupUI->Setup();
	return SetupUI;
}
