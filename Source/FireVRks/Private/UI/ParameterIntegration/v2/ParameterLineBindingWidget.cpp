#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"

#include "FX/Niagara/v2/MapParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "UI/DFUIUtil.h"

void UParameterLineBindingWidget::Initialize(UAbstractFormalParameter* FParameter, UParameterValueContext* Context)
{
	DFStyleUtil::LineBorderStyle(Border);

	auto Line = UDFUIUtil::AddUserWidget<UDFUILine>(Border);

	auto NameBox = UDFUIUtil::AddLabel(WidgetTree, Line->GetMountingPoint(), FParameter->GetDisplayName());
	Cast<UHorizontalBoxSlot>(NameBox->Slot)->SetPadding(FMargin(0, 0, 30, 0));

	DFStyleUtil::TextBlockStyle(NameBox);

	ChildWidget = UParamUtil::GetValueWidget(this, Context->Get(FParameter), FParameter->GetType());
	Line->Append(ChildWidget->AsWidget());
	ChildWidget->Initialize(Context->Get(FParameter));
	ChildWidget->DefaultStyle();
	DFStyleUtil::SafeSetHBoxSlotWidth(ChildWidget->AsWidget()->Slot, FSlateChildSize(ESlateSizeRule::Fill));
}

UPanelWidget* UParameterLineBindingWidget::MakeRootWidget(UWidgetTree* Tree)
{
	Border = UDFUIUtil::MakeWidget<UBorder>(Tree);
	return Border;
}

UPanelWidget* UParameterLineBindingWidget::GetMountingPoint()
{
	return Border;
}

void UParameterLineBindingWidget::WriteToContext(UParameterValueContext* Context)
{
	Context->SetValue(Parameter, ChildWidget->GetValue(Context));
}
