#include "UI/ParameterIntegration/SystemInstantiationBindingWidget.h"

#include "UI/ParameterIntegration/EffectParameterInputUI.h"
#include "UI/ParameterIntegration/SystemDisplayTile.h"
#include "FX/Niagara/SystemSettings/ParameterValues/SystemInstantiationParameterValue.h"
#include "UI/DFUIUtil.h"
#include "Unsafe/DFStyleUtil.h"

UPanelWidget* USystemInstantiationBindingWidget::MakeRootWidget(UWidgetTree* Tree)
{
	OuterBorder = DFUIUtil::MakeWidget<UBorder>(Tree);
	DFStyleUtil::BasicBorderStyle(OuterBorder, ESlateBrushDrawType::Box, DFStyleUtil::GREY_LVL_1);
	return OuterBorder;
}

void USystemInstantiationBindingWidget::Initialize(ParameterValueContext* Context, AbstractFormalParameter* Param)
{
	ParameterBindingWidget::Initialize(Context, Param);
	auto Value = static_cast<SystemInstantiationParameterValue*>(Context->Get(Param));
	System = Value->GetSystem();

	auto VBox = DFUIUtil::AddWidget<UVerticalBox>(WidgetTree, OuterBorder);
	auto Box = DFUIUtil::AddWidget<UHorizontalBox>(WidgetTree, VBox);

	auto ParamName = DFUIUtil::AddLabel(WidgetTree, Box, Param->GetName());
	DFStyleUtil::SafeSetHBoxSlotWidth(ParamName->Slot, FSlateChildSize(ESlateSizeRule::Fill));
	DFStyleUtil::TextBlockStyle(ParamName);

	auto SysSelector = DFUIUtil::AddUserWidget<USystemDisplayTile>(Box);
	DFStyleUtil::SafeSetHBoxSlotWidth(SysSelector->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	SysSelector->SetSystem(System, 96);

	InstanceParamUI = DFUIUtil::AddWidget<UEffectParameterInputUI>(WidgetTree, VBox);
	InstanceParamUI->SetSystem(System);
	InstanceParamUI->Draw(Value->GetContext());
}

void USystemInstantiationBindingWidget::SetValueInContext(MapParameterValueContext* Context)
{
	auto InstanceContext = new MapParameterValueContext(false);
	InstanceParamUI->WriteParamsToContext(InstanceContext);
	InstanceContext->Depend();
	auto Val = new SystemInstantiationParameterValue(System, InstanceContext, false);
	Context->SetValue(Parameter->GetGUID(), Val);
}

void USystemInstantiationBindingWidget::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	Callbacks.Add(Callback);
	InstanceParamUI->SubscribeToChanges(Callback);
}

void USystemInstantiationBindingWidget::CleanUp()
{
	Super::CleanUp();
	OuterBorder->RemoveFromParent();

	InstanceParamUI->CleanUp();
}
