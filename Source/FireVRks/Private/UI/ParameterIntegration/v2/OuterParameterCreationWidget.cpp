// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/OuterParameterCreationWidget.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "Kismet/GameplayStatics.h"
#include "DFUI/DFUI.h"
#include "UI/EDFUI.h"
#include "UI/ParameterIntegration/v2/ParameterCreatorInput.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"

void UOuterParameterCreationWidget::NewParameter(UWidget* Widget)
{
	auto Input = Cast<UParameterCreatorInput>(Widget);
	auto Param = UParamUtil::NewParam(System, Input->GetParamName(), Input->GetRequired(), Input->GetType());

	System->NewParameter(Param);

	UMapParameterValueContext* Context = UMapParameterValueContext::Instance(this);
	UParameterRenderer::RenderParam(this, Context, Param, PARAMETER_CREATION);
}

void UOuterParameterCreationWidget::OnAddParameter()
{
	auto Ctrlr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto Popup = EDFUI::OpenInputPopup<UParameterCreatorInput>(Ctrlr, "Create the new parameter");

	Popup->GetOnConfirm()->AddUniqueDynamic(this, &UOuterParameterCreationWidget::NewParameter);
}

void UOuterParameterCreationWidget::Draw()
{
	Box->ClearChildren();

	auto Context = UMapParameterValueContext::Instance(this);

	auto ParamValues = TArray<UAbstractFormalParameter*>();
	System->GetOuterParametersInOrder(ParamValues);
	for (UAbstractFormalParameter* Param : ParamValues)
	{
		UParameterRenderer::RenderParam(this, Context, Param, PARAMETER_CREATION);
	}
}

UPanelWidget* UOuterParameterCreationWidget::MakeRootWidget()
{
	RootBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2);

	auto OuterBox = DFUI::AddWidget<UVerticalBox>(RootBorder);

	auto PanelBorder = DFUI::AddWidget<UBorder>(OuterBox);
	DFStyleUtil::BasicBorderStyle(PanelBorder, DFStyleUtil::GREY_LVL_3);

	auto HBox = DFUI::AddWidget<UHorizontalBox>(PanelBorder);
	auto AddParamButton = DFUI::AddButtonToButtonPanel(HBox, "Add parameter");
	AddParamButton->OnPressed.AddUniqueDynamic(this, &UOuterParameterCreationWidget::OnAddParameter);

	Box = DFUI::AddWidget<UDFVBoxEx>(OuterBox);

	return RootBorder;
}

UPanelWidget* UOuterParameterCreationWidget::GetMountingPoint()
{
	return Box;
}

void UOuterParameterCreationWidget::SetSystem(UCustomEffectSystem* bSystem)
{
	this->System = bSystem;
}

void UOuterParameterCreationWidget::MoveUp(UParameterBindingWidget* Widget)
{
	Box->MoveUp(Widget);
	System->MoveOuterParameterUp(Widget->GetParameter()->GetId());
}

void UOuterParameterCreationWidget::MoveDown(UParameterBindingWidget* Widget)
{
	Box->MoveDown(Widget);
	System->MoveOuterParameterDown(Widget->GetParameter()->GetId());
}
