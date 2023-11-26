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

	auto Param = UParamUtil::NewParam(this, Input->GetParamName(), Input->GetRequired(), Input->GetType());
	Context->GetOuterParameters().Add(Param);
	
	Draw(Context);
}

void UOuterParameterCreationWidget::OnAddParameter()
{
	auto Ctrlr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto Popup = UDFUIUtil::OpenInputPopup<UParameterCreatorInput>(Ctrlr, "Create the new parameter");

	Popup->GetOnConfirm()->AddUniqueDynamic(this, &UOuterParameterCreationWidget::NewParameter);
}

void UOuterParameterCreationWidget::Draw(UBindingParameterValueContext* InContext)
{
	Context = InContext;
	Box->ClearChildren();
	
	for(UAbstractFormalParameter* Param : Context->GetOuterParameters())
	{
		UParameterRenderer::RenderParam(this, Context, Param, PARAMETER_CREATION);
	}
}

UPanelWidget* UOuterParameterCreationWidget::MakeRootWidget(UWidgetTree* Tree)
{
	RootBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(RootBorder, DFStyleUtil::GREY_LVL_1);

	auto OuterBox = UDFUIUtil::AddWidget<UVerticalBox>(Tree, RootBorder);

	auto PanelBorder = UDFUIUtil::AddWidget<UBorder>(Tree, OuterBox);
	DFStyleUtil::BasicBorderStyle(PanelBorder, DFStyleUtil::GREY_LVL_2);

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
