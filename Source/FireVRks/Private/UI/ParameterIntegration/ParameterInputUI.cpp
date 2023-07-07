#include "UI/ParameterIntegration/ParameterInputUI.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "FX/Niagara/Scheduler/EffectSystemScheduler.h"
#include "FX/Niagara/System/DefaultParameterSystem.h"
#include "UI/DFUIUtil.h"
#include "UI/ParameterIntegration/DFUIParameterBindingWidgetBase.h"
#include "UI/ParameterIntegration/ParamUIInputWidgetCallback.h"
#include "Unsafe/DFStyleUtil.h"
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
	for (AbstractFormalParameter* Parameter : System->GetOuterParameters())
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
	this->GetMountingPoint()->ClearChildren();
	this->Draw(Context);
}

void UParameterInputUI::SpawnSystem(AActor* Target)
{
	UEffectSystemScheduler::INSTANCE->SpawnNow(System, Target, FVector::Zero(), FVector(0,0,1), Context);
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


