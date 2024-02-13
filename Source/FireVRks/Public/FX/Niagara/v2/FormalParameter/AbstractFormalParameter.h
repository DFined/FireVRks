#pragma once
#include "ParameterType.h"
#include "FX/Niagara/v2/ParameterPredicate.h"
#include "FX/Niagara/v2/TruePredicate.h"
#include "Util/DFId.h"
#include "AbstractFormalParameter.generated.h"

#define DF_PARAMETER_GETTER(OuterType, InnerType) \
	InnerType GetValue(UParameterValueContext* Context) \
	{ \
		return UParamUtil::GetTypedValue<OuterType, InnerType>(Context->Get(this)); \
	};

UCLASS()
class FIREVRKS_API UAbstractFormalParameter : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UAbstractParameterValue* Default;

	UPROPERTY()
	UDFId* Id;

	ParameterType Type;

	ParameterPredicate* Predicate = new TruePredicate();

	FString DisplayName;

	bool Required;
public:
	UAbstractParameterValue* DefaultValue() const;

	void SetDefault(UAbstractParameterValue* bDefault);

	UDFId* GetId();

	ParameterPredicate* GetPredicate() const;
	
	bool IsRequired() const;

	ParameterType GetType() const;
	
	FString GetDisplayName();

	void SetId(UDFId* Id);

	void SetPredicate(ParameterPredicate* Predicate);

	void SetRequired(bool bRequired);	

	void SetType(ParameterType Type);

	void SetDisplayName(const FString& DisplayName);

	TSharedPtr<FJsonObject> ToJson();

	virtual ~UAbstractFormalParameter() override;

	static UAbstractFormalParameter* FromJson(TSharedPtr<FJsonObject> Json, UObject* Outer);
};
