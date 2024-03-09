#include "UI/ParameterIntegration/v2/ParameterLineBindingWidget.h"

#include "FX/Niagara/v2/BindingParameterValueContext.h"
#include "FX/Niagara/v2/ParamUtil.h"
#include "FX/Niagara/v2/System/SubsystemConfig.h"
#include "DFUI/DFUI.h"
#include "UI/Icons.h"
#include "UI/CoreUI/EffectEditorUI.h"
#include "UI/lib/Container/DFUILine.h"
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
	auto OuterWidget = DFUI::AttemptFindWidgetByType<UOuterParameterCreationWidget>(this);
	OuterWidget->MoveUp(this);
}

void UParameterLineBindingWidget::MoveDown()
{
	auto OuterWidget = DFUI::AttemptFindWidgetByType<UOuterParameterCreationWidget>(this);
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
		auto BindingContext = Cast<UBindingParameterValueContext>(Context);
		auto SelectedParam = BindSelector->GetSelectedParam();
		if (SelectedParam)
		{
			BindingContext->GetBindings()->GetBindings().Add(Parameter->GetId(), SelectedParam);
			ChildWidget->AsWidget()->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			BindingContext->GetBindings()->GetBindings().Remove(Parameter->GetId());
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

	auto Line = DFUI::AddWidget<UDFUILine>(Border);

	auto NameBox = DFUI::AddLabel(Line->GetMountingPoint(), Parameter->GetDisplayName());
	Cast<UHorizontalBoxSlot>(NameBox->Slot)->SetPadding(FMargin(0, 0, 30, 0));
	DFStyleUtil::SafeSetHBoxSlotWidth(NameBox->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill, VAlign_Center);

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
		break;
	case PARAMETER_CREATION:
		ChildWidget->Initialize(Parameter->DefaultValue());
		break;
	}

	Line->Append(ChildWidget->AsWidget());


	ChildWidget->DefaultStyle();
	DFStyleUtil::SafeSetHBoxSlotWidth(ChildWidget->AsWidget()->Slot, FSlateChildSize(ESlateSizeRule::Fill), HAlign_Fill,
	                                  VAlign_Center);

	if (DrawType == PARAMETER_CREATION)
	{
		auto UpBtn = DFUI::AddImageButton(Line->GetMountingPoint(), UDFStatics::ICONS->UP_ICON, 24);
		DFStyleUtil::SafeSetHBoxSlotWidth(UpBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		UpBtn->OnPressed.AddUniqueDynamic(this, &UParameterLineBindingWidget::MoveUp);

		auto DownBtn = DFUI::AddImageButton(Line->GetMountingPoint(), UDFStatics::ICONS->DOWN_ICON,
		                                          24);
		DFStyleUtil::SafeSetHBoxSlotWidth(DownBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		DownBtn->OnPressed.AddUniqueDynamic(this, &UParameterLineBindingWidget::MoveDown);

		auto DeleteBtn = DFUI::AddImageButton(Line->GetMountingPoint(),
		                                            UDFStatics::ICONS->DELETE_ICON, 32);
		DFStyleUtil::SafeSetHBoxSlotWidth(DeleteBtn->Slot, FSlateChildSize(ESlateSizeRule::Automatic));
		DeleteBtn->OnPressed.AddUniqueDynamic(this, &UParameterLineBindingWidget::OnDelete);
	}
	if (IsBinding)
	{
		auto System = DFU::AttemptFindObjectByType<UCustomEffectSystem>(Context);
		System->GetEventCallback().AddUniqueDynamic(this, &UParameterLineBindingWidget::ProcessSystemEvent);

		TArray<UAbstractFormalParameter*> AvailableParams = TArray<UAbstractFormalParameter*>();
		System->FindAvailableOuters(Parameter->GetType(), AvailableParams);
		BindSelector = DFUI::MakeWidget<UParamBindingSelectionWidget>(this);
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


UPanelWidget* UParameterLineBindingWidget::MakeRootWidget()
{
	Border = DFUI::MakeWidget<UBorder>(this);
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

void UParameterLineBindingWidget::RedrawParentBlock()
{
	auto Block = DFUI::AttemptFindWidgetByType<UBlockParameterBindingWidget>(this);
	if (Block)
	{
		Block->Redraw();
	}
}

void UParameterLineBindingWidget::OnChange()
{
	switch (DrawType)
	{
	case PARAMETER_CREATION:
		Parameter->SetDefault(ChildWidget->GetValue(Parameter));
		break;
	case SYSTEM_INSTANCE_PARAMS:
		{
			Context->SetValue(Parameter, ChildWidget->GetValue(Context));
			RedrawParentBlock();
			break;
		}
	case INNER_SYSTEM_BINDING:
		if (auto BindingContext = Cast<UBindingParameterValueContext>(Context))
		{
			BindingContext->GetBindings()->GetConstantValues().Add(Parameter->GetId(), ChildWidget->GetValue(Context));
			RedrawParentBlock();
		}
		break;
	}
}
