#include "Util/DFManaged.h"

DFManaged::DFManaged(bool bManaged): Managed(bManaged)
{
	Dependants = 0;
}

void DFManaged::Depend()
{
	Dependants++;
}

void DFManaged::Release()
{
	Dependants--;
}

bool DFManaged::IsDependedOn() const
{
	return Dependants > 0 || Managed;
}

void DFManaged::SafeRelease(DFManaged* Obj)
{
	Obj->Release();
	if (!Obj->IsDependedOn())
	{
		delete(Obj);
	}
}
