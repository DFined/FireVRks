#pragma once
#include "DFType.h"

class DFTyped
{
	/**
	* The number of dependants on this value. Should be increased when adding to a dependant and decreased when no longer needed or when dependant is destroyed 
	*/
	int Dependants = 0;
	/**
	 * If true, disallows deletion even if Terminal is set to true; 
	 */
	bool Managed;
public:
	explicit DFTyped(bool bManaged)
		: Managed(bManaged)
	{
		Dependants = 0;
	}

	virtual ~DFTyped() = default;
	virtual DFType GetType() PURE_VIRTUAL("Get", return DFType::NONE;);

	
	void Depend()
	{
		Dependants++;
	}

	void Release()
	{
		Dependants--;
	}

	bool IsDependedOn() const
	{
		return Dependants > 0 || Managed;
	}
};
