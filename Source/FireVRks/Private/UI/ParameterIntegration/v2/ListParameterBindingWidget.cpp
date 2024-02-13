// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterIntegration/v2/ListParameterBindingWidget.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/FormalParameter/ListFormalParameter.h"
#include "FX/Niagara/v2/ParameterValue/ListParameterValue.h"
#include "DFUI/DFUI.h"
#include "UI/lib/Container/DFUILine.h"
#include "UI/lib/Container/DFUIStack.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"

class UDFUILine;

UPanelWidget* UListParameterBindingWidget::MakeRootWidget()
{
	OuterBorder = DFUI::MakeWidget<UBorder>(this);
	DFStyleUtil::BasicBorderStyle(OuterBorder, DFStyleUtil::GREY_LVL_2);
	return OuterBorder;
}

UPanelWidget* UListParameterBindingWidget::GetMountingPoint()
{
	return ListStack->GetMountingPoint();
}

void UListParameterBindingWidget::NewItem()
{
	UParameterValueContext* PVContext;
	auto ListVal = Cast<UListParameterValue>(Context->Get(Parameter));
	if(DrawType == INNER_SYSTEM_BINDING)
	{
		auto BContext = UBindingParameterValueContext::New(Context);
		BContext->SetBindings(USubsystemParameterBindings::Instance(BContext));
		BContext->SetOuterContext(UMapParameterValueContext::Instance(BContext));
		PVContext = BContext;
		ListVal->AddValue(PVContext);
		auto BindContext = Cast<UBindingParameterValueContext>(Context);
		BindContext->GetBindings()->GetConstantValues().Add(Parameter->GetId(), ListVal);
	}
	else
	{
		PVContext = UMapParameterValueContext::Instance(Context);
		ListVal->AddValue(PVContext);
	}
	AddWidgetFromParam(PVContext, Cast<UListFormalParameter>(Parameter)->GetChildType());
	this->OnChange();
	this->LayoutChanged();
}

void UListParameterBindingWidget::AddWidgetFromParam(UParameterValueContext* SubContext,
                                                     UAbstractFormalParameter* ChildType)
{
	auto NewWidget = UParameterRenderer::RenderParam(ListStack, SubContext, ChildType, DrawType);
	NewWidget->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UListParameterBindingWidget::LayoutChanged);
}

void UListParameterBindingWidget::InitializeBindingWidget()
{
	auto OuterVBox = DFUI::AddWidget<UVerticalBox>(OuterBorder);
	auto HeaderBox = DFUI::AddWidget<UDFUILine>(OuterVBox);
	auto NameLabel = DFUI::AddLabel(HeaderBox->GetMountingPoint(), Parameter->GetDisplayName());
	if (UHorizontalBoxSlot* TSlot = Cast<UHorizontalBoxSlot>(NameLabel->Slot))
	{
		TSlot->SetPadding(FMargin(0, 0, 30, 0));
		TSlot->SetVerticalAlignment(VAlign_Center);
	}
	auto Button = DFUI::AddWidget<UButton>(HeaderBox);
	DFUI::AddLabel(Button, "Create new");
	DFStyleUtil::TextButtonStyle(Button, DFStyleUtil::GREY_LVL_2);
	Button->OnPressed.AddUniqueDynamic(this, &UListParameterBindingWidget::NewItem);

	ListStack = DFUI::AddWidget<UDFUIStack>(OuterVBox);

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
	for (UWidget* Widget : ListStack->GetMountingPoint()->GetAllChildren())
	{
		if (auto ParamWidget = Cast<UParameterBindingWidget>(Widget))
		{
			UMapParameterValueContext* NewContext = NewObject<UMapParameterValueContext>(
				Value, UMapParameterValueContext::StaticClass());
			Value->AddValue(NewContext);
			ParamWidget->WriteToContext(NewContext);
		}
	}
	bContext->SetValue(this->Parameter, Value);
}


