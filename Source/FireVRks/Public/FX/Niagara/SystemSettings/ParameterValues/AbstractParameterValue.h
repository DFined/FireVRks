#pragma once
#include "Util/DFTyped.h"

class AbstractParameterValue : public DFTyped
{

public:
	explicit AbstractParameterValue(bool bManaged)
		: DFTyped(bManaged)
	{
	}

	virtual DFType GetType() override PURE_VIRTUAL("GetType", return DFType::NONE;);
};
