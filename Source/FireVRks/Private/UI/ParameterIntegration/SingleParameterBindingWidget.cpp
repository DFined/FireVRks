#include "UI/ParameterIntegration/SingleParameterBindingWidget.h"

#include "Components/HorizontalBoxSlot.h"
#include "UI/DFUIUtil.h"
#include "Unsafe/ParameterIntegration/ParameterTypingUtil.h"

UPanelWidget* USingleParameterBindingWidget::MakeRootWidget(UWidgetTree* Tree)
{
	Border = DFUIUtil::MakeWidget<UBorder>(Tree);
	return Border;
}

void USingleParameterBindingWidget::Initialize(ParameterValueContext* Value, AbstractFormalParameter* Param)
{
	Parameter = Param;
	auto ParamUtil = ParameterTypingUtil::GetParamUtil(Parameter->GetType());
	if (ParamUtil)
	{
		ChildWidget = ParamUtil->CreateInput(this->WidgetTree);
	}
	if (ChildWidget)
	{
		DFStyleUtil::LineBorderStyle(Border);

		auto Line = DFUIUtil::AddUserWidget<UDFUILine>(Border);

		auto NameBox = DFUIUtil::AddLabel(WidgetTree, Line->GetMountingPoint(), Parameter->GetName());
		Cast<UHorizontalBoxSlot>(NameBox->Slot)->SetPadding(FMargin(0, 0, 30, 0));

		DFStyleUtil::TextBlockStyle(NameBox);

		auto Widget = ChildWidget->AsWidget();
		Line->Append(Widget);
		auto BoxSlot = Cast<UHorizontalBoxSlot>(Widget->Slot);
		if (BoxSlot)
		{
			BoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			BoxSlot->SetHorizontalAlignment(HAlign_Fill);
			BoxSlot->SetVerticalAlignment(VAlign_Fill);
		}
		ChildWidget->DefaultStyle();
		ChildWidget->Initialize(Value, Param);
	}
}

AbstractParameterValue* USingleParameterBindingWidget::GetValue()
{
	return ChildWidget->GetValue();
}

void USingleParameterBindingWidget::SubscribeToChanges(WidgetCallbackWithValue* Callback)
{
	ChildWidget->SubscribeToChanges(Callback);
}
