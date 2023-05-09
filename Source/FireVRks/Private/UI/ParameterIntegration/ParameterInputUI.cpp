#include "UI/ParameterIntegration/ParameterInputUI.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/SystemSettings/ParamSystem/DefaultParameterSystem.h"
#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/ParamUIInputWidgetCallback.h"
#include "Unsafe/DFStyleUtil.h"
#include "Unsafe/ParameterIntegration/DFParameterUtil.h"


UParameterInputUI::UParameterInputUI()
{
	Parameters = TArray<AbstractFormalParameter*>();
}

UParameterInputUI::~UParameterInputUI()
{
	if (Context)
	{
		delete(Context);
	}
	for (AbstractFormalParameter* Param : Parameters)
	{
		Param->Release();
		if(!Param->IsDependedOn())
		{
			delete(Param);
		}
	}
}

UPanelWidget* UParameterInputUI::MakeRootWidget(UWidgetTree* Tree)
{
	auto Border = DFUIUtil::MakeWidget<UBorder>(Tree);
	VerticalBox = DFUIUtil::AddWidget<UVerticalBox>(Tree, Border);
	DFStyleUtil::BasicBorderStyle(Border, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_2);
	return Border;
}

UPanelWidget* UParameterInputUI::GetMountingPoint()
{
	return VerticalBox;
}

void UParameterInputUI::WriteParamsToContext(MapParameterValueContext* bContext)
{
	DFParameterUtil::SetContextValuesFromUI(bContext, this->GetMountingPoint());
}

void UParameterInputUI::AddParameter(AbstractFormalParameter* Parameter)
{
	Parameters.Add(Parameter);
	Parameter->Depend();
}

void UParameterInputUI::AddParameters(TArray<AbstractFormalParameter*> ParameterList)
{
	for(AbstractFormalParameter* Param: ParameterList)
	{
		Parameters.Add(Param);
	}
}

void UParameterInputUI::DumpToContext()
{
	if (Context)
	{
		delete(Context);
	}
	Context = new MapParameterValueContext();
	this->WriteParamsToContext(Context);
}

void UParameterInputUI::Draw(ParameterValueContext* InitialContext)
{
	for (AbstractFormalParameter* Parameter : this->Parameters)
	{
		if(Parameter->GetDisplayPredicate()->Check(InitialContext))
		{
			auto PBW = UParameterRenderer::RenderParam(this, InitialContext, Parameter);
			PBW->SubscribeToChanges(new ParamUIInputWidgetCallback(this));
			DumpToContext();
		}
	}
}

void UParameterInputUI::OnChildWidgetValueChange(ParameterBindingWidget* PBW, AbstractParameterValue* Value)
{
	DumpToContext();
	auto MountingPoint = this->GetMountingPoint();
	MountingPoint->ClearChildren();
	this->Draw(Context);
}

UDefaultParameterSystem* UParameterInputUI::GetSystem()
{
	auto System = NewObject<UDefaultParameterSystem>(this);
	System->SetContext(Context);
	
	return System;
}
