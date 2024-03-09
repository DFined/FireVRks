#include "Util/DFId.h"

bool FDFId::operator==(const FDFId& Other) const
{
	return this->Hash == Other.Hash ? this->Id.Equals(Other.Id): false;
}

TSharedPtr<FDFId> FDFId::Named(FString Fidd)
{
	auto Ptr = MakeShared<FDFId>();
	Ptr->SetId(Fidd);
	return Ptr;
}

TSharedPtr<FDFId> FDFId::Random()
{
	auto Ptr = MakeShared<FDFId>();
	Ptr->SetId(FGuid::NewGuid().ToString());
	return Ptr;
}

FString FDFId::GetId() const
{
	return Id;
}

void FDFId::SetId(FString Fid)
{
	this->Id = Fid;
	this->Hash = TextKeyUtil::HashString(Fid);
}

uint32 GetTypeHash(const FDFId fId)
{
	return fId.Hash;
}
