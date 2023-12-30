#include "World/Launcher/ArrayLaunchPattern.h"

#include "FX/Niagara/Scheduler/LaunchSettings.h"

TMap<UDFId*, UAbstractFormalParameter*>* UArrayLaunchPattern::GetOuterParameters()
{
	return &Parameters;
}

void UArrayLaunchPattern::Init()
{
	if (!IsInit)
	{
		Parameters = TMap<UDFId*, UAbstractFormalParameter*>();
		Add(ARRAY_LAUNCH_SETTING);
		Add(ARRAY_NAME);
		Add(SYSTEMS);

		ARRAY_LAUNCH_SETTING->Add(ARRAY_TRAVERSAL_TYPE);
		ARRAY_LAUNCH_SETTING->Add(INVERT_ORDER);
		ARRAY_LAUNCH_SETTING->Add(DELAY_BETWEEN_SHOTS);

		LAUNCHER_SETTING->Add(SHELL_LIFETIME);
		LAUNCHER_SETTING->Add(SHELL_VELOCITY);
		LAUNCHER_SETTING->Add(SYSTEM_PICKER);

		IsInit = true;
	}
}

void UArrayLaunchPattern::Launch(UParameterValueContext* Context, float CommonDelay, bool IsTest) const
{
	if (const auto LauncherArray = ARRAY_NAME->GetValue(Context))
	{
		const auto Launchers = LauncherArray->GetLaunchers();
		int StartNum = 0;
		int EndNum = Launchers->Num();
		const bool Invert = INVERT_ORDER->GetValue(Context);
		const float Delay = DELAY_BETWEEN_SHOTS->GetValue(Context);
		for (int i = StartNum; i < EndNum; i++)
		{
			for (const auto SystemContext : SYSTEMS->GetValue(Context))
			{
				const auto Launcher = (*Launchers)[Invert ? EndNum - i - 1 : i];
			
				const auto SystemInstanceParams = Cast<USystemInstantiationParameterValue>(SystemContext->Get(SYSTEM_PICKER));

				auto SpawnData = ULaunchSettings::Make(
					Launcher,
					UDFStatics::EFFECT_SYSTEM_MANAGER->Get(SystemInstanceParams->GetSystem()),
					SystemInstanceParams->GetContext(),
					Launcher,
					CommonDelay + Delay * i,
					SHELL_LIFETIME->GetValue(SystemContext),
					SHELL_VELOCITY->GetValue(SystemContext)
				);

				IsTest ? UDFStatics::GetCoordinator()->EnqueueTest(SpawnData) : UDFStatics::GetCoordinator()->EnqueueDisplay(SpawnData);
			}
		}
	}
}

UArrayLaunchPattern* UArrayLaunchPattern::MakeInstance()
{
	const auto Obj = NewObject<UArrayLaunchPattern>(GetTransientPackage());
	Obj->AddToRoot();
	Obj->Init();
	return Obj;
}

void UArrayLaunchPattern::Add(UAbstractFormalParameter* Parameter)
{
	Parameters.Add(Parameter->GetId(), Parameter);
}

void UArrayLaunchPattern::GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result)
{
	DFU::GetValues(Parameters, Result);
}
