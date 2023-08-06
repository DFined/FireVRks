#pragma once
#include "GenericLauncherArray.h"
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/EnumFormalParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/SystemInstantiationFormalParameter.h"

class ArrayLaunchTraversalPattern
{
	inline static bool IsInit = false;

public:
	inline static BlockCompoundParameter ARRAY_LAUNCH_SETTING = BlockCompoundParameter("Array settings", true, true, true);
	inline static EnumFormalParameter ARRAY_TRAVERSAL_TYPE = EnumFormalParameter(
		"Array traversal direction", true, &EnumLike::ARRAY_TRAVERSAL_MODE, true
	);
	inline static FormalParameter<bool> INVERT_ORDER = FormalParameter(DFType::TYPED_BOOL_PARAMETER, "Invert order", true, false, true);
	inline static FormalParameter<float> DELAY_BETWEEN_SHOTS = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Delay between shots", true, 0.5f, true);
	
	inline static BlockCompoundParameter LAUNCHER_SETTING = BlockCompoundParameter("Launch settings", true, true, true);
	inline static FormalParameter<float> SHELL_LIFETIME = FormalParameter(DFType::TYPED_FLOAT_PARAMETER, "Shell Lifetime", true, 2.0f, true);
	inline static FormalParameter<int> SHELL_VELOCITY = FormalParameter(DFType::TYPED_INT_PARAMETER, "Shell Velocity", true, 10000, true);
	SystemInstantiationFormalParameter SYSTEM_PICKER = SystemInstantiationFormalParameter("System", true);

	static TArray<AbstractFormalParameter*> GetParameters();

	static void Init()
	{
		if (!IsInit)
		{
			IsInit = true;
			ARRAY_LAUNCH_SETTING.AddChild(&ARRAY_TRAVERSAL_TYPE);
			ARRAY_LAUNCH_SETTING.AddChild(&INVERT_ORDER);
			ARRAY_LAUNCH_SETTING.AddChild(&DELAY_BETWEEN_SHOTS);
		}
	}

	static void Launch(ParameterValueContext* Context, UGenericLauncherArray* LauncherArray, USystemAndContext* SystemAndContext)
	{
		auto Launchers = LauncherArray->GetLaunchers();
		int StartNum = 0;
		int EndNum = Launchers->Num();
		bool Invert = INVERT_ORDER.GetValue(Context);
		float Delay = DELAY_BETWEEN_SHOTS.GetValue(Context);
		for (int i = StartNum; i < EndNum; i++)
		{
			(*Launchers)[Invert ? EndNum - i : i]->Fire(SystemAndContext, i * Delay, SHELL_LIFETIME.GetValue(Context), SHELL_VELOCITY.GetValue(Context));
		}
	}
};
