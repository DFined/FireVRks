#include "UI/ParameterIntegration/ParameterInputUI.h"

#include "UI/ParameterIntegration/ParamUIInputWidgetCallback.h"
#include "FX/Niagara/SystemSettings/InstanceParameter/MapParameterValueContext.h"
#include "UI/DFUIUtil.h"
#include "Unsafe/ParameterIntegration/DFParameterUtil.h"

UParameterInputUI::UParameterInputUI()
{
}

UParameterInputUI::~UParameterInputUI()
{
	if (Context)
	{
		delete(Context);
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

void UParameterInputUI::DumpToContext()
{
	if (Context)
	{
		delete(Context);
	}
	Context = new MapParameterValueContext(true);
	this->WriteParamsToContext(Context);
}

void UParameterInputUI::Draw(ParameterValueContext* InitialContext)
{
	for (AbstractFormalParameter* Parameter : ParamProvider->GetOuterParameters())
	{
		if(Parameter->GetDisplayPredicate()->Check(InitialContext))
		{
			auto PBW = UParameterRenderer::RenderParam(this, InitialContext, Parameter);
			PBW->SubscribeToChanges(new ParamUIInputWidgetCallback(this));
			DumpToContext();
		}
	}
}

void UParameterInputUI::OnChildWidgetValueChange(ParameterBindingWidget* Widget, AbstractParameterValue* Value)
{
	DumpToContext();
	this->GetMountingPoint()->ClearChildren();
	this->Draw(Context);
}

void UParameterInputUI::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	for (UWidget* Widget : this->GetMountingPoint()->GetAllChildren())
	{
		if(ParameterBindingWidget* PBW = Cast<UDFUIParameterBindingWidgetBase>(Widget))
		{
			PBW->SubscribeToChanges(Callback);
		}
	}
}

UParameterValueContextProvider* UParameterInputUI::GetContextProvider()
{
	return USimplePVCProvider::Of(this->Context, this);
}

void UParameterInputUI::CleanUp()
{
	this->CleanUpBindingWidgets();
	VerticalBox->RemoveFromParent();
}
