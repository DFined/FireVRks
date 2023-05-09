#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"



EnumLikeValue::EnumLikeValue(FString Id, FString Name): Parent(nullptr), Id(Id), Name(Name)
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

bool operator==(const EnumLikeValue& Lhs, const EnumLikeValue& RHS)
{
	return Lhs.Id == RHS.Id
		&& Lhs.Name == RHS.Name;
}

bool operator!=(const EnumLikeValue& Lhs, const EnumLikeValue& RHS)
{
	return !(Lhs == RHS);
}
