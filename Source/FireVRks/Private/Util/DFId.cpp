#include "Util/DFId.h"

bool UDFId::operator==(const UDFId& Other) const
{
	return this->Hash == Other.Hash ? this->Id.Equals(Other.Id): false;
}

uint32 UDFId::GetTypeHash(const UDFId* fId)
{
	return fId->Hash;
}

uint32 UDFId::PreHash(const FString& Fid)
{
	return FCrc::MemCrc32(&Fid, sizeof(FGuid));
}

UDFId* UDFId::Named(UObject* Outer, const FString& Fid)
{
	auto Id = NewObject<UDFId>(Outer, StaticClass());
	Id->Id = Fid;
	Id->Hash = Id->PreHash(Fid);
	return Id;
}

UDFId* UDFId::Random(UObject* Outer)
{
	auto Id = NewObject<UDFId>(Outer, StaticClass());
	auto Str = FGuid::NewGuid().ToString();
	Id->Id = Str;
	Id->Hash = Id->PreHash(Str);
	return Id;
}

FString UDFId::GetId() const
{
	return Id;
}
