#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "UI/DFUIUtil.h"
#include "UI/Icons.h"
#include "UI/CoreUI/EffectEditorUI.h"
#include "UI/ParameterIntegration/v2/BlockParameterBindingWidget.h"
#include "UI/ParameterIntegration/v2/OuterParameterCreationWidget.h"
#include "UI/ParameterIntegration/v2/ParamBindingSelectionWidget.h"

void UParameterLineBindingWidget::OnDelete()
{
	this->RemoveFromParent();
	auto System = DFU::AttemptFindObjectByType<UCustomEffectSystem>(Parameter);
	System->DeleteParameter(this->Parameter);
}

void UParameterLineBindingWidget::MoveUp()
{
	auto OuterWidget = UDFUIUtil::AttemptFindWidgetByType<UOuterParameterCreationWidget>(this);
	OuterWidget->MoveUp(this);
}

void UParameterLineBindingWidget::MoveDown()
{
	auto OuterWidget = UDFUIUtil::AttemptFindWidgetByType<UOuterParameterCreationWidget>(this);
	OuterWidget->MoveDown(this);
}

void UParameterLineBindingWidget::ProcessSystemEvent(UDFEvent* Event)
{
	switch (Event->GetType())
	{
	case CUSTOM_SYSTEM_PARAMETER_CREATED:
		{
			auto Param = Cast<UDFParameterEvent>(Event)->GetParameter();
			if (Param->GetType() == this->Parameter->GetType())
			{
				this->BindSelector->AddOptionParam(Param);
			}
			break;
		}
	case CUSTOM_SYSTEM_PARAMETER_DELETED:
		{
			auto Param = Cast<UDFParameterEvent>(Event)->GetParameter();
			if (this->BindSelector->GetSelectedIndex() > 0)
			{
				this->BindSelector->RemoveOptionParam(Param);
				this->ChildWidget->AsWidget()->SetVisibility(ESlateVisibility::Visible);
			}
			break;
		}
	default: ;
	}
}

void UParameterLineBindingWidget::OnParamBound(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType != ESelectInfo::Type::Direct)
	{
		auto Config = DFU::AttemptFindObjectByType<USubsystemConfig>(Context);
		auto SelectedParam = BindSelector->GetSelectedParam();
		if (SelectedParam)
		{
			Config->GetBindings()->GetBindings().Add(Parameter->GetId(), SelectedParam);
			ChildWidget->AsWidget()->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			Config->GetBindings()->GetBindings().Remove(Parameter->GetId());
			ChildWidget->AsWidget()->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UParameterLineBindingWidget::InitializeBindingWidget()
{
	auto BindingContext = Cast<UBindingParameterValueContext>(Context);
	bool IsBinding = BindingContext && DrawType == INNER_SYSTEM_BINDING;
	auto BoundParameter = BindingContext ? BindingContext->FindBinding(this->Parameter->GetId()) : nullptr;


	DFStyleUtil::LineBorderStyle(Border);

	auto Line = UDFUIUtil::AddUserWidget<UDFUILine>(Border);

	auto NameBox = UDFUIUtil::AddLabel(WidgetTree, Line->GetMountingPoint(), Parameter->GetDisplayName());
	Cast<UHorizontalBoxSlot>(NameBox->Slot)->SetPadding(FMargin(0, 0, 30, 0));
	DFStyleUtil::SafeSetHBoxSlotWidth(NameBox->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill, VAlign_Center);

	DFStyleUtil::TextBlockStyle(NameBox);


	ChildWidget = UParamUtil::GetValueWidget(this, Parameter->GetType());
	switch (DrawType)
	{
	case SYSTEM_INSTANCE_PARAMS:
		ChildWidget->Initialize(Context->Get(Parameter));
		break;
	case INNER_SYSTEM_BINDING:
		{
			auto Constants = BindingContext->GetBindings()->GetConstantValues();
			auto Default = Constants.Find(Parameter->GetId());
			ChildWidget->Initialize(Default ? *Default : Parameter->DefaultValue());
		}
	case PARAMETER_CREATION:
		ChildWidget->Initialize(Parameter->DefaultValue());
	}

	Line->Append(ChildWidget->AsWidget());


	ChildWidget->DefaultStyle();
	DFStyleUtil::SafeSetHBoxSlotWidth(ChildWidget->AsWidget()->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill,
	                                  VAlign_Center);

	if (DrawType == PARAMETER_CREATION)
	{
		auto UpBtn = UDFUIUtil::MakeImageButton(WidgetTree, Line->GetMountingPoint(), &Icons::UP_ICON, 24);
		DFStyleUtil::SafeSetHBoxSlotWidth(UpBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		UpBtn->OnPressed.AddUniqueDynamic(this, &UParameterLineBindingWidget::MoveUp);

		auto DownBtn = UDFUIUtil::MakeImageButton(WidgetTree, Line->GetMountingPoint(), &Icons::DOWN_ICON, 24);
		DFStyleUtil::SafeSetHBoxSlotWidth(DownBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		DownBtn->OnPressed.AddUniqueDynamic(this, &UParameterLineBindingWidget::MoveDown);

		auto DeleteBtn = UDFUIUtil::MakeImageButton(WidgetTree, Line->GetMountingPoint(), &Icons::DELETE_ICON, 32);
		DFStyleUtil::SafeSetHBoxSlotWidth(DeleteBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		DeleteBtn->OnPressed.AddUniqueDynamic(this, &UParameterLineBindingWidget::OnDelete);
	}
	if (IsBinding)
	{
		auto System = DFU::AttemptFindObjectByType<UCustomEffectSystem>(Context);
		System->GetEventCallback().AddUniqueDynamic(this, &UParameterLineBindingWidget::ProcessSystemEvent);

		TArray<UAbstractFormalParameter*> AvailableParams = TArray<UAbstractFormalParameter*>();
		System->FindAvailableOuters(Parameter->GetType(), AvailableParams);
		BindSelector = UDFUIUtil::MakeWidget<UParamBindingSelectionWidget>(WidgetTree);
		BindSelector->ReInit(AvailableParams);
		DFStyleUtil::ComboBox(BindSelector);
		BindSelector->OnSelectionChanged.AddUniqueDynamic(this, &UParameterLineBindingWidget::OnParamBound);

		Line->Append(BindSelector);

		if (BoundParameter)
		{
			BindSelector->SetSelectedOption(BoundParameter->GetDisplayName());
			ChildWidget->AsWidget()->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			BindSelector->SetSelectedOption("None");
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

void UParameterLineBindingWidget::WriteToContext(UParameterValueContext* bContext)
{
	bContext->SetValue(Parameter, ChildWidget->GetValue(bContext));
}

void UParameterLineBindingWidget::OnChange()
{
	switch (DrawType)
	{
	case PARAMETER_CREATION:
		Parameter->SetDefault(ChildWidget->GetValue(Parameter));
	case SYSTEM_INSTANCE_PARAMS:
		{
			Context->SetValue(Parameter, ChildWidget->GetValue(Context));
			auto Block = UDFUIUtil::AttemptFindWidgetByType<UBlockParameterBindingWidget>(this);
			if (Block)
			{
				Block->Redraw();
			}
			break;
		}
	case INNER_SYSTEM_BINDING:
		auto Config = DFU::AttemptFindObjectByType<USubsystemConfig>(Context);
		Config->GetBindings()->GetConstantValues().Add(Parameter->GetId(), ChildWidget->GetValue(Config));
	}
}
