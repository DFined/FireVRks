#pragma once
#include "FX/Niagara/SystemSettings/FormalParameter/AbstractFormalParameter.h"
#include "UI/ParameterIntegration/BlockUIStateParameterValue.h"

/**
 * A generalization of a parameter into a list of child parameters
 */
class BlockCompoundParameter : public AbstractFormalParameter
{
public:
	virtual AbstractParameterValue* GetDefault() override;

private:
	TArray<AbstractFormalParameter*> ChildParameters;
	BlockUIStateParameterValue Default;
public:
	BlockCompoundParameter(const FString& GUID, FString& Name,
	const TArray<AbstractFormalParameter*>& ChildParameters, bool Required, bool bManaged, bool expanded)
	: AbstractFormalParameter(GUID, Name, DFType::COMPOUND_BLOCK_PARAMETER, Required, bManaged), ChildParameters(ChildParameters),
	Default(BlockUIStateParameterValue(expanded, true))
	{
	}

	explicit BlockCompoundParameter(FString Name, bool Required, bool bManaged, bool expanded)
	: AbstractFormalParameter(FGuid::NewGuid().ToString(), Name, DFType::COMPOUND_BLOCK_PARAMETER, Required, bManaged),
	Default(BlockUIStateParameterValue(expanded, true))
	{
	}

	void AddChild(AbstractFormalParameter* Parameter);

	TArray<AbstractFormalParameter*> GetChildParameters() const;

	virtual ~BlockCompoundParameter() override;	
};
