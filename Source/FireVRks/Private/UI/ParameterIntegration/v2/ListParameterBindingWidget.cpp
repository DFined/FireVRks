// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ListParameterBindingWidget.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/FormalParameter/ListFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/ListParameterValue.h"
#include "UI/DFUIUtil.h"
#include "UI/lib/Container/DFUIStack.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"

UPanelWidget* UListParameterBindingWidget::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_2);
	return OuterBorder;
}

UPanelWidget* UListParameterBindingWidget::GetMountingPoint()
{
	return ListStack->GetMountingPoint();
}

void UListParameterBindingWidget::NewItem()
{
	AddWidgetFromParam(UMapParameterValueContext::New(this), Cast<UListFormalParameter>(Parameter)->GetChildType());
	this->OnChange();
}

void UListParameterBindingWidget::AddWidgetFromParam(UParameterValueContext* SubContext, UAbstractFormalParameter* ChildType)
{
	UParameterRenderer::RenderParam(ListStack, SubContext, ChildType);
}

void UListParameterBindingWidget::Initialize(UAbstractFormalParameter* fParameter, UParameterValueContext* Context)
{
	auto OuterVBox = DFUIUtil::AddWidget<UVerticalBox>(this->WidgetTree, OuterBorder);
	auto HeaderBox = DFUIUtil::AddUserWidget<UDFUILine>(OuterVBox);
	auto NameLabel = DFUIUtil::AddLabel(this->WidgetTree, HeaderBox->GetMountingPoint(), fParameter->GetDisplayName());
	DFStyleUtil::TextBlockStyle(NameLabel);
	if(UHorizontalBoxSlot* TSlot = Cast<UHorizontalBoxSlot>(NameLabel->Slot))
	{
		TSlot->SetPadding(FMargin(0,0,30,0));
		TSlot->SetVerticalAlignment(VAlign_Center);
	}
	auto Button = DFUIUtil::AddWidget<UButton>(HeaderBox);
	DFUIUtil::AddLabel(WidgetTree, Button, "Create new");
	DFStyleUtil::TextButtonStyle(Button, DFStyleUtil::GREY_LVL_2);
	Button->OnPressed.AddUniqueDynamic(this, &UListParameterBindingWidget::NewItem);

	ListStack = DFUIUtil::AddUserWidget<UDFUIStack>(OuterVBox);


	auto Vals = Cast<UListParameterValue>(Context->Get(Parameter));
	auto ListParam = Cast<UListFormalParameter>(Parameter);
	for (UParameterValueContext* SubContext : Vals->Get())
	{
		AddWidgetFromParam(SubContext, ListParam->GetChildType());
	}
}

void UListParameterBindingWidget::WriteToContext(UParameterValueContext* Context)
{
	auto Value = NewObject<UListParameterValue>(Context, UListParameterValue::StaticClass());
	for(UWidget* Widget: ListStack->GetMountingPoint()->GetAllChildren())
	{
		if(auto ParamWidget = Cast<UParameterBindingWidget>(Widget))
		{
			UMapParameterValueContext* NewContext = NewObject<UMapParameterValueContext>(Value, UMapParameterValueContext::StaticClass());
			Value->AddValue(NewContext);
			ParamWidget->WriteToContext(NewContext);
		}
	}
	Context->SetValue(this->Parameter, Value);
}


