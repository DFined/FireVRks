#include "UI/ParameterIntegration/v2/ArrayLaunchParameterInputUI.h"

#include "Util/DFStatics.h"
#include "World/Launcher/ArrayLaunchPattern.h"

void UArrayLaunchParameterInputUI::Launch()
{
	DumpToContext();
	UDFStatics::GetArrayLaunchPattern()->Launch(Context);
}

UArrayLaunchParameterInputUI* UArrayLaunchParameterInputUI::InstanceEmpty(UPanelWidget* Widget)
{
	auto MockValueContext = NewObject<UMapParameterValueContext>(Widget, UMapParameterValueContext::StaticClass());
	return Instance(Widget, MockValueContext);
}

UArrayLaunchParameterInputUI* UArrayLaunchParameterInputUI::Instance(UPanelWidget* Widget, UParameterValueContext* fContext)
{
	if(!fContext)
	{
		return InstanceEmpty(Widget);
	}
	auto NewWidget = DFUIUtil::AddUserWidget<UArrayLaunchParameterInputUI>(Widget);
	NewWidget->SetProvider(UDFStatics::ARRAY_LAUNCH_PATTERN);
	
	NewWidget->Draw(fContext);
	return NewWidget;
}
