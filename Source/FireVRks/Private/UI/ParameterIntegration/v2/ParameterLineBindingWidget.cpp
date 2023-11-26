#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "UI/DFUIUtil.h"
#include "UI/Icons.h"
#include "UI/ParameterIntegration/v2/BlockParameterBindingWidget.h"
#include "UI/ParameterIntegration/v2/ParamBindingSelectionWidget.h"

void UParameterLineBindingWidget::InitializeBindingWidget()
{
	auto BindingContext = Cast<UBindingParameterValueContext>(Context);
	bool IsBinding = BindingContext && DrawType == INNER_SYSTEM_BINDING;
	auto BoundParameter = BindingContext->FindBinding(this->Parameter->GetId());


	DFStyleUtil::LineBorderStyle(Border);

	auto Line = UDFUIUtil::AddUserWidget<UDFUILine>(Border);

	auto NameBox = UDFUIUtil::AddLabel(WidgetTree, Line->GetMountingPoint(), Parameter->GetDisplayName());
	Cast<UHorizontalBoxSlot>(NameBox->Slot)->SetPadding(FMargin(0, 0, 30, 0));
	DFStyleUtil::SafeSetHBoxSlotWidth(NameBox->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill, VAlign_Center);

	DFStyleUtil::TextBlockStyle(NameBox);


	if (!BoundParameter || !IsBinding)
	{
		ChildWidget = UParamUtil::GetValueWidget(this, Context->Get(Parameter), Parameter->GetType());
		Line->Append(ChildWidget->AsWidget());

		ChildWidget->Initialize(Context->Get(Parameter));
		ChildWidget->DefaultStyle();
		DFStyleUtil::SafeSetHBoxSlotWidth(ChildWidget->AsWidget()->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill, VAlign_Center);
	}

	if (DrawType == PARAMETER_CREATION)
	{
		auto UpBtn = UDFUIUtil::MakeImageButton(WidgetTree, Line->GetMountingPoint(), &Icons::UP_ICON, 24);
		DFStyleUtil::SafeSetHBoxSlotWidth(UpBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		auto DownBtn = UDFUIUtil::MakeImageButton(WidgetTree, Line->GetMountingPoint(), &Icons::DOWN_ICON, 24);
		DFStyleUtil::SafeSetHBoxSlotWidth(DownBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		auto DeleteBtn = UDFUIUtil::MakeImageButton(WidgetTree, Line->GetMountingPoint(), &Icons::DELETE_ICON, 32);
		DFStyleUtil::SafeSetHBoxSlotWidth(DeleteBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
	}
	if (BindingContext && DrawType == INNER_SYSTEM_BINDING)
	{
		if (BoundParameter)
		{
			auto ParamName = UDFUIUtil::NamedWidget<UTextBlock>(Line->GetMountingPoint(), WidgetTree, "Bound To: ");
			ParamName->SetText(FText::FromString(BoundParameter->GetDisplayName()));
			DFStyleUtil::TextBlockStyle(ParamName);
		}
		else
		{
			TArray<UAbstractFormalParameter*> OuterParams = TArray<UAbstractFormalParameter*>();
			BindingContext->FindAvailableOuters(Parameter->GetType(), OuterParams);
			auto BindSelector = UDFUIUtil::AddWidget<UParamBindingSelectionWidget>(Line);
			DFStyleUtil::ComboBox(BindSelector);
			BindSelector->ReInit(OuterParams);
		}
	}
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

void UParameterLineBindingWidget::OnChange()
{
	switch (DrawType)
	{
		case PARAMETER_CREATION:
			break;
		case SYSTEM_INSTANCE_PARAMS:
			Context->SetValue(Parameter, ChildWidget->GetValue(Context));
			auto Block = UDFUIUtil::AttemptFindWidgetByType<UBlockParameterBindingWidget>(this);
			Block->Redraw();
			break;
		case INNER_SYSTEM_BINDING:
			break;
	}
}
