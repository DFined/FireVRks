#include "UI/ParameterIntegration/v2/ParameterInputUI.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/v2/ParameterRenderer.h"

UPanelWidget* UParameterInputUI::MakeRootWidget(UWidgetTree* Tree)
{
	auto Border = UDFUIUtil::MakeWidget<UBorder>(Tree);
	VerticalBox = UDFUIUtil::AddWidget<UVerticalBox>(Tree, Border);
	DFStyleUtil::BasicBorderStyle(Border, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_2);
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
	for (UAbstractFormalParameter* Parameter : *Provider->GetOuterParameters())
	{
		if(Parameter->GetPredicate()->Check(InitialContext))
		{
			auto NewParam = UParameterRenderer::RenderParam(this, InitialContext, Parameter);
			NewParam->GetLayoutChangeDelegate()->AddUniqueDynamic(this, &UParameterInputUI::LayoutChanged);
		}
	}
	DumpToContext();
}

void UParameterInputUI::OnChange()
{
	DumpToContext();
	this->GetMountingPoint()->ClearChildren();
	this->Draw(Context);
}