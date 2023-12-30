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
	OuterBorder = UDFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, DFStyleUtil::GREY_LVL_2);
	return OuterBorder;
}

UPanelWidget* UListParameterBindingWidget::GetMountingPoint()
{
	return ListStack->GetMountingPoint();
}

void UListParameterBindingWidget::NewItem()
{
	AddWidgetFromParam(UMapParameterValueContext::Instance(this), Cast<UListFormalParameter>(Parameter)->GetChildType());
	this->OnChange();
	this->LayoutChanged();
}

void UListParameterBindingWidget::AddWidgetFromParam(UParameterValueContext* SubContext, UAbstractFormalParameter* ChildType)
{
	auto NewWidget = UParameterRenderer::RenderParam(ListStack, SubContext, ChildType, DrawType);
	NewWidget->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UListParameterBindingWidget::LayoutChanged);
}

void UListParameterBindingWidget::InitializeBindingWidget()
{
	this->DrawType = DrawType;
	auto OuterVBox = UDFUIUtil::AddWidget<UVerticalBox>(this->WidgetTree, OuterBorder);
	auto HeaderBox = UDFUIUtil::AddUserWidget<UDFUILine>(OuterVBox);
	auto NameLabel = UDFUIUtil::AddLabel(this->WidgetTree, HeaderBox->GetMountingPoint(), Parameter->GetDisplayName());
	DFStyleUtil::TextBlockStyle(NameLabel);
	if(UHorizontalBoxSlot* TSlot = Cast<UHorizontalBoxSlot>(NameLabel->Slot))
	{
		TSlot->SetPadding(FMargin(0,0,30,0));
		TSlot->SetVerticalAlignment(VAlign_Center);
	}
	auto Button = UDFUIUtil::AddWidget<UButton>(HeaderBox);
	UDFUIUtil::AddLabel(WidgetTree, Button, "Create new");
	DFStyleUtil::TextButtonStyle(Button, DFStyleUtil::GREY_LVL_2);
	Button->OnPressed.AddUniqueDynamic(this, &UListParameterBindingWidget::NewItem);

	ListStack = UDFUIUtil::AddUserWidget<UDFUIStack>(OuterVBox);


	auto Vals = Cast<UListParameterValue>(Context->Get(Parameter));
	auto ListParam = Cast<UListFormalParameter>(Parameter);
	for (UParameterValueContext* SubContext : Vals->Get())
	{
		AddWidgetFromParam(SubContext, ListParam->GetChildType());
	}
}

void UListParameterBindingWidget::WriteToContext(UParameterValueContext* bContext)
{
	auto Value = NewObject<UListParameterValue>(bContext, UListParameterValue::StaticClass());
	for(UWidget* Widget: ListStack->GetMountingPoint()->GetAllChildren())
	{
		if(auto ParamWidget = Cast<UParameterBindingWidget>(Widget))
		{
			UMapParameterValueContext* NewContext = NewObject<UMapParameterValueContext>(Value, UMapParameterValueContext::StaticClass());
			Value->AddValue(NewContext);
			ParamWidget->WriteToContext(NewContext);
		}
	}
	bContext->SetValue(this->Parameter, Value);
}


