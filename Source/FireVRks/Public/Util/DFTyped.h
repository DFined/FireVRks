#pragma once
#include "DFManaged.h"
#include "DFType.h"

class DFTyped : public DFManaged
{
public:
	explicit DFTyped(bool NManaged) : DFManaged(NManaged){};

	virtual ~DFTyped() = default;
	virtual DFType GetType() PURE_VIRTUAL("Get", return DFType::NONE;);
	
};
