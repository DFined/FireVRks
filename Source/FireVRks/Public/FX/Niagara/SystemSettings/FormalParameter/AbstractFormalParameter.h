#pragma once
#include "ParameterPredicate.h"
#include "TruePredicate.h"
#include "FX/Niagara/SystemSettings/ParameterValues/AbstractParameterValue.h"
#include "Util/DFTyped.h"

class AbstractFormalParameter : public DFTyped
{
	FGuid GUID;
	FString Name;
	DFType ValueType;
	bool Required;

protected:
	ParameterPredicate* DisplayPredicate = new TruePredicate();

public:
	AbstractFormalParameter(const FString& GUID, FString& Name, DFType ValueType, bool IsRequired, bool bManaged)
		: GUID(GUID), Name(Name), ValueType(ValueType), Required(IsRequired), DFTyped(bManaged)
	{
	}

	[[nodiscard]] FGuid GetGUID() const
	{
		return GUID;
	}

	virtual DFType GetType() override;

	FString GetName() const
	{
		return Name;
	}

	bool IsRequired() const
	{
		return Required;
	}

	virtual AbstractParameterValue* GetDefault();

	DFType GetValueType() const
	{
		return ValueType;
	}

	void SetDisplayPredicate(ParameterPredicate* DPredicate)
	{
		if (DisplayPredicate) { delete(DisplayPredicate); }
		this->DisplayPredicate = DPredicate;
	}

	ParameterPredicate* GetDisplayPredicate() const
	{
		return DisplayPredicate;
	}

	virtual ~AbstractFormalParameter() override;
};
