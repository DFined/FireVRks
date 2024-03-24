#include "World/Launcher/ArrayLaunchPattern.h"

#include "FX/Niagara/Scheduler/EffectSpawnCoordinator.h"
#include "FX/Niagara/Scheduler/LaunchSettings.h"
#include "FX/Niagara/v2/System/EffectSystemManager.h"

TMap<FDFId, UAbstractFormalParameter*>* UArrayLaunchPattern::GetOuterParameters()
{
	return &Parameters;
}

void UArrayLaunchPattern::Init()
{
	if (!IsInit)
	{
		Parameters = TMap<FDFId, UAbstractFormalParameter*>();
		Add(ARRAY_NAME);
		Add(ARRAY_LAUNCH_SETTING);
		Add(LAUNCHER_SETTING);
		Add(SYSTEMS);

		ARRAY_LAUNCH_SETTING->Add(ARRAY_TRAVERSAL_TYPE);
		ARRAY_LAUNCH_SETTING->Add(INVERT_ORDER);
		ARRAY_LAUNCH_SETTING->Add(DELAY_BETWEEN_SHOTS);

		LAUNCHER_ARRAY_SETTING->Add(SHELL_LIFETIME);
		LAUNCHER_ARRAY_SETTING->Add(SHELL_VELOCITY);
		LAUNCHER_ARRAY_SETTING->Add(SYSTEM_PICKER);

		LAUNCHER_SETTING->Add(LAUNCHER_TRAVERSAL_TYPE);
		LAUNCHER_SETTING->Add(NUMBER_OF_SHOTS);
		LAUNCHER_SETTING->Add(ANGLE_STEP);
		LAUNCHER_SETTING->Add(TIME_STEP);
		LAUNCHER_SETTING->Add(STARTING_ANGLE);

		IsInit = true;
	}
}

void UArrayLaunchPattern::QueueNewSystem(float Delay, bool IsTest, UParameterValueContext* SystemContext, AGenericFireworkLauncher* Launcher,
                                         USystemInstantiationParameterValue* SystemInstanceParams, float Roll) const
{
	auto LifetimeSemivariance = SHELL_LIFETIME_VARIANCE->GetValue(SystemContext);
	auto SpawnData = ULaunchSettings::Make(
		Launcher,
		UEffectSystemManager::GetInstance()->Get(SystemInstanceParams->GetSystem()),
		SystemInstanceParams->GetContext(),
		Launcher,
		Delay,
		SHELL_LIFETIME->GetValue(SystemContext) + FMath::RandRange(-LifetimeSemivariance, LifetimeSemivariance),
		SHELL_VELOCITY->GetValue(SystemContext),
		Roll
	);

	IsTest ? UDFStatics::GetCoordinator()->EnqueueTest(SpawnData) : UDFStatics::GetCoordinator()->EnqueueDisplay(SpawnData);
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

				int StartingAngle = STARTING_ANGLE->GetValue(Context);
				int Step = ANGLE_STEP->GetValue(Context);
				float TimeStep = TIME_STEP->GetValue(Context);
				int NumSteps = NUMBER_OF_SHOTS->GetValue(Context);

				const auto SystemInstanceParams = Cast<USystemInstantiationParameterValue>(SystemContext->Get(SYSTEM_PICKER));
				for (int j = 0; j < NumSteps; ++j)
				{
					switch (LAUNCHER_TRAVERSAL_TYPE->GetValue(Context)->GetOrdinal())
					{
					case 0: //END_TO_END
						QueueNewSystem(
							CommonDelay + Delay * i + j * TimeStep, IsTest, SystemContext, Launcher, SystemInstanceParams, StartingAngle + Step * j
						);
						break;
					case 1: //FROM_CENTER
						QueueNewSystem(
							CommonDelay + Delay * i + j * TimeStep, IsTest, SystemContext, Launcher, SystemInstanceParams, StartingAngle + Step * j
						);
						QueueNewSystem(
							CommonDelay + Delay * i + j * TimeStep, IsTest, SystemContext, Launcher, SystemInstanceParams, StartingAngle - Step * j
						);
						break;
					case 2: //FROM_BOTH_ENDS
						QueueNewSystem(
							CommonDelay + Delay * i + j * TimeStep, IsTest, SystemContext, Launcher, SystemInstanceParams, StartingAngle - Step * (NumSteps - j)
						);
						QueueNewSystem(
							CommonDelay + Delay * i + j * TimeStep, IsTest, SystemContext, Launcher, SystemInstanceParams, StartingAngle + Step * (NumSteps - j)
						);
						break;
					default: throw std::invalid_argument("Unknown traversal type");
					}
				}
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
