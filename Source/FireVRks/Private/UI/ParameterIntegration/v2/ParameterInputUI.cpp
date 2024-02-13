#include "UI/ParameterIntegration/v2/ParameterInputUI.h"

#include "Components/Border.h"
#include "DFUI/DFUI.h"
#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"

UPanelWidget* UParameterInputUI::MakeRootWidget()
{
	auto Border = DFUI::MakeBorder(this, DFStyleUtil::GREY_LVL_2);
	VerticalBox = DFUI::AddWidget<UVerticalBox>(Border);
	return Border;
}


UPanelWidget* UParameterInputUI::GetMountingPoint()
{
	return VerticalBox;
}

void UParameterInputUI::DumpToContext()
{
	Context = NewObject<UMapParameterValueContext>(this,UMapParameterValueContext::StaticClass());
	WriteToContext(Context);
}

void UParameterInputUI::WriteToContext(UParameterValueContext* FillContext)
{
	UParamUtil::WriteContainerToContext(VerticalBox, FillContext);
}


void UParameterInputUI::Draw(UParameterValueContext* InitialContext)
{
	Draw(InitialContext, SYSTEM_INSTANCE_PARAMS);
}

void UParameterInputUI::Draw(UParameterValueContext* InitialContext, ParameterDrawType DrawType)
{
	auto OuterParameters = TArray<UAbstractFormalParameter*>();
	Provider->GetOuterParametersInOrder(OuterParameters);
	for (UAbstractFormalParameter* Parameter : OuterParameters)
	{
		if(Parameter->GetPredicate()->Check(InitialContext))
		{
			auto NewParam = UParameterRenderer::RenderParam(this, InitialContext, Parameter, DrawType);
			NewParam->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UParameterInputUI::LayoutChanged);
		}
	}
}

void UParameterInputUI::OnChange()
{
	DumpToContext();
	this->GetMountingPoint()->ClearChildren();
	this->Draw(Context);
}