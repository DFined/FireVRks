#include "UI/ParameterIntegration/v2/ArrayLaunchParameterInputUI.h"

#include "Util/DFStatics.h"
#include "World/Launcher/ArrayLaunchPattern.h"

void UArrayLaunchParameterInputUI::Launch(FString ArrayName) const
{
	auto Array = UDFStatics::LAUNCHER_MANAGER->FindLauncherArray(ArrayName);
	if (Array)
	{
		UDFStatics::ARRAY_LAUNCH_PATTERN->Launch(this->Context, Array);
	}
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
