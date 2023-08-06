#pragma once
#include "FX/Niagara/SystemSettings/InstanceParameter/ParameterValueContext.h"

#include "SystemAndContext.generated.h"

UCLASS()
class USystemAndContext : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	UEffectSystem* System;
	
	ParameterValueContext* Context;

public:
	UFUNCTION(BlueprintCallable)
	UEffectSystem* GetSystem() const
	{
		return System;
	}

	UFUNCTION(BlueprintCallable)
	void SetSystem(UEffectSystem* FSystem)
	{
		this->System = FSystem;
	}

	ParameterValueContext* GetContext() const
	{
		return Context;
	}

	void SetContext(ParameterValueContext* FContext)
	{
		this->Context = FContext;
	}
};
