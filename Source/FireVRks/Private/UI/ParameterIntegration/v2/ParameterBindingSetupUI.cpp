// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ParameterBindingSetupUI.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"
#include "UI/ParameterIntegration/v2/SystemDisplayTile.h"
#include "Util/DFStatics.h"

UPanelWidget* UParameterBindingSetupUI::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2);

	auto VBox = UDFUIUtil::AddWidget<UVerticalBox>(Tree, RootBorder);
	
	SystemDisplayTile = UDFUIUtil::AddUserWidget<USystemDisplayTile>(VBox);
	this->SetSystem(UDFStatics::GetDefaultEffectSystem());

	ParamsBox = UDFUIUtil::AddWidget<UVerticalBox>(Tree, VBox);
	return RootBorder;
}

void UParameterBindingSetupUI::Setup(UParameterValueContext* Context)
{
	for(auto Param : *System->GetOuterParameters())
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


UParameterBindingSetupUI* UParameterBindingSetupUI::InstanceFrom(UPanelWidget* Parent, UBindingParameterValueContext* Context)
{
	auto SetupUI = UDFUIUtil::AddUserWidget<UParameterBindingSetupUI>(Parent);
	SetupUI->Setup(Context);
	return SetupUI;
}
