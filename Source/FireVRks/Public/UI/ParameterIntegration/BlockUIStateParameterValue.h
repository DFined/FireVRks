#pragma once
#include "FX/Niagara/SystemSettings/ParameterValues/AbstractParameterValue.h"

/**
 * A bit of a dirty hack to allow the state of the UI to be stored and maintained alongside the parameters. This is required because the UI
 * is dynamic and required to be rebuildable completely from the parameter states. This acts as the value type for the block parameter type
 */
class BlockUIStateParameterValue : public AbstractParameterValue
{
	bool BlockExpanded;
	bool OverridesExpanded;
public:
	BlockUIStateParameterValue(bool expanded, bool bManaged)
		: AbstractParameterValue(bManaged), BlockExpanded(expanded), OverridesExpanded(false)
	{
	}

	BlockUIStateParameterValue(bool bManaged, bool bBlockExpanded, bool bOverridesExpanded)
		: AbstractParameterValue(bManaged),
		  BlockExpanded(bBlockExpanded),
		  OverridesExpanded(bOverridesExpanded)
	{
	}

	bool IsBlockExpanded() const
	{
		return BlockExpanded;
	}

	bool IsOverridesExpanded() const
	{
		return OverridesExpanded;
	}

	virtual DFType GetType() override;
};
