#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"



EnumLikeValue::EnumLikeValue(FString Id, FString Name, int bOrdinal): Id(Id), Name(Name), Parent(nullptr), Ordinal(bOrdinal)
{
}

EnumLike* EnumLikeValue::GetParent() const
{
	return Parent;
}

void EnumLikeValue::SetParent(EnumLike* Prnt)
{
	this->Parent = Prnt;
}

int EnumLikeValue::GetOrdinal() const
{
	return Ordinal;
}

FString EnumLikeValue::GetName() const
{
	return Name;
}

bool operator==(const EnumLikeValue& Lhs, const EnumLikeValue& RHS)
{
	return Lhs.Id == RHS.Id
		&& Lhs.Name == RHS.Name;
}

bool operator!=(const EnumLikeValue& Lhs, const EnumLikeValue& RHS)
{
	return !(Lhs == RHS);
}
