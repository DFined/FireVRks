#include "DFJsonUtil.h"

FVector DFJsonUtil::ReadVectorFromJson(TSharedPtr<FJsonObject> Json, FString Name)
{
	auto VecObj = Json->GetObjectField(Name);
	return FVector(VecObj->GetNumberField("X"), VecObj->GetNumberField("Y"), VecObj->GetNumberField("Z"));
}

FRotator DFJsonUtil::ReadRotatorFromJson(TSharedPtr<FJsonObject> Json, FString Name)
{
	auto VecObj = Json->GetObjectField(Name);
	return FRotator(VecObj->GetNumberField("Roll"), VecObj->GetNumberField("Pitch"), VecObj->GetNumberField("Yaw"));
}
