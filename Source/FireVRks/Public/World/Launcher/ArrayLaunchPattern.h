#pragma once
#include "FX/Niagara/v2/System/ParameterProvider.h"
#include "FX/Niagara/v2/FormalParameter/AbstractFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ArraySelectorParameter.h"
#include "FX/Niagara/v2/FormalParameter/BlockFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/BoolFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/EnumFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/FloatFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/IntFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/ListFormalParameter.h"
#include "FX/Niagara/v2/FormalParameter/SystemInstantiationFormalParameter.h"
#include "FX/Niagara/v2/System/DefaultParameterSystem.h"
#include "ArrayLaunchPattern.generated.h"


class AGenericFireworkLauncher;

UCLASS()
class FIREVRKS_API UArrayLaunchPattern : public UObject, public ParameterProvider
{
	GENERATED_BODY()

	bool IsInit = false;

	UPROPERTY()
	TMap<FDFId, UAbstractFormalParameter*> Parameters;

public:
	UPROPERTY()
	UBlockFormalParameter* ARRAY_LAUNCH_SETTING = UParamUtil::Global<UBlockFormalParameter, bool>("Array settings", true, true);
	UPROPERTY()
	UArraySelectorParameter* ARRAY_NAME = UParamUtil::Global<UArraySelectorParameter>("Array Name", true);
	UPROPERTY()
	UEnumFormalParameter* ARRAY_TRAVERSAL_TYPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>(
		"Array traversal direction", true, &EnumLikeValue::END_TO_END
	);
	UPROPERTY()
	UBoolFormalParameter* INVERT_ORDER = UParamUtil::Global<UBoolFormalParameter, bool>("Invert order", true, false);
	UPROPERTY()
	UFloatFormalParameter* DELAY_BETWEEN_SHOTS = UParamUtil::Global<UFloatFormalParameter, float>("Delay between shots", true, 0.5f);
	UPROPERTY()
	UFloatFormalParameter* ARRAY_DELAY_VARIANCE = UParamUtil::Global<UFloatFormalParameter, float>("Delay Variance", true, 0.15f);
	UPROPERTY()
	USystemInstantiationFormalParameter* SYSTEM_PICKER = UParamUtil::Global<USystemInstantiationFormalParameter, FDFId>(
		"System", true, UDFStatics::DEFAULT_SYSTEM_ID
	);
	UPROPERTY()
	UListFormalParameter* SYSTEMS = UParamUtil::Global<UListFormalParameter, UAbstractFormalParameter*>("Systems", true, SYSTEM_PICKER);
	UPROPERTY()
	UFloatFormalParameter* SHELL_LIFETIME = UParamUtil::Global<UFloatFormalParameter, float>("Shell Lifetime", true, 2.0f);
	UPROPERTY()
	UFloatFormalParameter* SHELL_LIFETIME_VARIANCE = UParamUtil::Global<UFloatFormalParameter, float>("Shell Lifetime Variance", true, 0.15f);
	UPROPERTY()
	UIntFormalParameter* SHELL_VELOCITY = UParamUtil::Global<UIntFormalParameter, int>("Shell Velocity", true, 6500);

	UPROPERTY()
	UBlockFormalParameter* LAUNCHER_SETTING = UParamUtil::Global<UBlockFormalParameter, bool>("Launcher settings", true, true);
	UPROPERTY()
	UEnumFormalParameter* LAUNCHER_TRAVERSAL_TYPE = UParamUtil::Global<UEnumFormalParameter, EnumLikeValue*>(
		"Array traversal direction", true, &EnumLikeValue::END_TO_END
	);
	UPROPERTY()
	UIntFormalParameter* NUMBER_OF_SHOTS = UParamUtil::Global<UIntFormalParameter, int>("Number of shots", true, 1);
	UPROPERTY()
	UFloatFormalParameter* TIME_STEP = UParamUtil::Global<UFloatFormalParameter, float>("LauncherDelayBetweenShots", "Delay between shots", true, 0.5);
	UPROPERTY()
	UFloatFormalParameter* TIME_STEP_VARIANCE = UParamUtil::Global<UFloatFormalParameter, float>("DelayBetweenShotsVariance", "Delay Variance", true, 0.15f);
	UPROPERTY()
	UIntFormalParameter* ANGLE_STEP = UParamUtil::Global<UIntFormalParameter, int>("Angle between shots", true, 10);
	UPROPERTY()
	UIntFormalParameter* STARTING_ANGLE = UParamUtil::Global<UIntFormalParameter, int>("Starting angle", true, 0);


	virtual TMap<FDFId, UAbstractFormalParameter*>* GetOuterParameters() override;

	void Init();
	void QueueNewSystem(float Delay, bool IsTest, UParameterValueContext* ArrayOuterContext, AGenericFireworkLauncher* Launcher,
		USystemInstantiationParameterValue* SystemInstanceParams, float Roll) const;

	void Launch(UParameterValueContext* Context, float Delay, bool IsTest) const;

	static UArrayLaunchPattern* MakeInstance();

	void Add(UAbstractFormalParameter* Parameter);

	virtual void GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result) override;
};
