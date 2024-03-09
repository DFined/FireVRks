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
	UBlockFormalParameter* LAUNCHER_SETTING = UParamUtil::Global<UBlockFormalParameter, bool>("Launch settings", true, true);
	UPROPERTY()
	UListFormalParameter* SYSTEMS = UParamUtil::Global<UListFormalParameter, UAbstractFormalParameter*>("Systems", true, LAUNCHER_SETTING);
	UPROPERTY()
	UFloatFormalParameter* SHELL_LIFETIME = UParamUtil::Global<UFloatFormalParameter, float>("Shell Lifetime", true, 2.0f);
	UPROPERTY()
	UIntFormalParameter* SHELL_VELOCITY = UParamUtil::Global<UIntFormalParameter, int>("Shell Velocity", true, 6500);
	UPROPERTY()
	USystemInstantiationFormalParameter* SYSTEM_PICKER = UParamUtil::Global<USystemInstantiationFormalParameter, FDFId>(
		"System", true, UDFStatics::DEFAULT_SYSTEM_ID
	);

	virtual TMap<FDFId, UAbstractFormalParameter*>* GetOuterParameters() override;

	void Init();
	
	void Launch(UParameterValueContext* Context, float Delay, bool IsTest) const;

	static UArrayLaunchPattern* MakeInstance();

	void Add(UAbstractFormalParameter* Parameter);

	virtual void GetOuterParametersInOrder(TArray<UAbstractFormalParameter*>& Result) override;
};
