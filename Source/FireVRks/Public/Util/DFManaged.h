#pragma once

class DFManaged
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
	
	explicit DFManaged(bool bManaged);

	void Depend();

	void Release();

	bool IsDependedOn() const;

	static void SafeRelease(DFManaged* Obj);
};
