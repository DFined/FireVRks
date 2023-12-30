// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/OuterParameterCreationWidget.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DFUIUtil.h"
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
	auto Popup = UDFUIUtil::OpenInputPopup<UParameterCreatorInput>(Ctrlr, "Create the new parameter");

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

UPanelWidget* UOuterParameterCreationWidget::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_2);

	auto OuterBox = UDFUIUtil::AddWidget<UVerticalBox>(Tree, RootBorder);

	auto PanelBorder = UDFUIUtil::AddWidget<UBorder>(Tree, OuterBox);
	DFStyleUtil::BasicBorderStyle(PanelBorder, DFStyleUtil::GREY_LVL_3);

	auto HBox = UDFUIUtil::AddWidget<UHorizontalBox>(Tree, PanelBorder);
	auto AddParamButton = UDFUIUtil::AddButtonToButtonPanel(HBox, "Add parameter", Tree);
	AddParamButton->OnPressed.AddUniqueDynamic(this, &UOuterParameterCreationWidget::OnAddParameter);

	Box = UDFUIUtil::AddWidget<UVerticalBox>(Tree, OuterBox);

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
	UDFUIUtil::MoveChildUp(this->GetMountingPoint(), Widget);
	System->MoveOuterParameterUp(Widget->GetParameter()->GetId());
}

void UOuterParameterCreationWidget::MoveDown(UParameterBindingWidget* Widget)
{
	UDFUIUtil::MoveChildDown(this->GetMountingPoint(), Widget);
	System->MoveOuterParameterDown(Widget->GetParameter()->GetId());
}
