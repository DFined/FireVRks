#include "World/Launcher/ArrayLaunchPattern.h"

#include "World/Launcher/LaunchSettings.h"

TArray<UAbstractFormalParameter*>* UArrayLaunchPattern::GetOuterParameters()
{
	return &Parameters;
}

void UArrayLaunchPattern::Init()
{
	if (!IsInit)
	{
		Parameters = TArray<UAbstractFormalParameter*>();
		Parameters.Add(ARRAY_LAUNCH_SETTING);
		Parameters.Add(ARRAY_NAME);
		Parameters.Add(SYSTEMS);
		
		ARRAY_LAUNCH_SETTING->Add(ARRAY_TRAVERSAL_TYPE);
		ARRAY_LAUNCH_SETTING->Add(INVERT_ORDER);
		ARRAY_LAUNCH_SETTING->Add(DELAY_BETWEEN_SHOTS);
		
		LAUNCHER_SETTING->Add(SHELL_LIFETIME);
		LAUNCHER_SETTING->Add(SHELL_VELOCITY);
		LAUNCHER_SETTING->Add(SYSTEM_PICKER);

		IsInit = true;
	}
}

void UArrayLaunchPattern::Launch(UParameterValueContext* Context, UGenericLauncherArray* LauncherArray)
{
	auto SystemInstanceParams = Cast<USystemInstantiationParameterValue>(Context->Get(SYSTEM_PICKER));

	auto Launchers = LauncherArray->GetLaunchers();
	int StartNum = 0;
	int EndNum = Launchers->Num();
	bool Invert = INVERT_ORDER->GetValue(Context);
	float Delay = DELAY_BETWEEN_SHOTS->GetValue(Context);
	for (int i = StartNum; i < EndNum; i++)
	{
		auto Launcher = (*Launchers)[Invert ? EndNum - i - 1: i];
		auto LaunchSettings = ULaunchSettings::Make(
			Context,
			UDFStatics::EFFECT_SYSTEM_MANAGER->Get(SystemInstanceParams->GetSystem()),
			SystemInstanceParams->GetContext(),
			SHELL_LIFETIME->GetValue(Context),
			SHELL_VELOCITY->GetValue(Context)
		);
		if (Delay * i > 0)
		{
			FTimerDelegate Delegate = FTimerDelegate();
			Delegate.BindUFunction(Launcher, FName("Fire"), LaunchSettings);
			auto IgnoredHandle = FTimerHandle();
			Launcher->GetWorldTimerManager().SetTimer(IgnoredHandle, Delegate, Delay * i, false);
		}
		else
		{
			Launcher->Fire(LaunchSettings);
		}
	}
}

UArrayLaunchPattern* UArrayLaunchPattern::MakeInstance()
{
	auto Obj = NewObject<UArrayLaunchPattern>(GetTransientPackage());
	Obj->AddToRoot();
	Obj->Init();
	return Obj;
}
