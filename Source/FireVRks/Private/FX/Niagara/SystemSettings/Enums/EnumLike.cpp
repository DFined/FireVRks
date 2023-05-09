#include "FX/Niagara/SystemSettings/Enums/EnumLike.h"

#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"

EnumLikeValue EnumLikeValue::PEONY = EnumLikeValue("PEONY", "Peony");
EnumLikeValue EnumLikeValue::BURST = EnumLikeValue("BURST", "Burst");
EnumLikeValue EnumLikeValue::RING = EnumLikeValue("RING", "Ring");
EnumLikeValue EnumLikeValue::DISK = EnumLikeValue("DISK", "Disk");
EnumLikeValue EnumLikeValue::CONE = EnumLikeValue("CONE", "Cone");
EnumLikeValue EnumLikeValue::QUASAR = EnumLikeValue("QUASAR", "Quasar");
EnumLikeValue EnumLikeValue::MULTI_CONE = EnumLikeValue("MULTI_CONE", "Multi cone");

EnumLikeValue EnumLikeValue::CRACKLE = EnumLikeValue("CRACKLE", "Crackle");
EnumLikeValue EnumLikeValue::GLITTER = EnumLikeValue("GLITTER", "Glitter");
EnumLikeValue EnumLikeValue::SMOKE = EnumLikeValue("SMOKE", "Smoke");
EnumLikeValue EnumLikeValue::SPARK = EnumLikeValue("SPARK", "Spark");

EnumLike EnumLike::BURST_SHAPE = EnumLike(
	{
		&EnumLikeValue::PEONY,
		&EnumLikeValue::BURST,
		&EnumLikeValue::RING,
		&EnumLikeValue::DISK,
		&EnumLikeValue::CONE,
		&EnumLikeValue::QUASAR,
		&EnumLikeValue::MULTI_CONE
	}
);

EnumLike EnumLike::TRAIL_TYPE = EnumLike(
	{
		&EnumLikeValue::CRACKLE,
		&EnumLikeValue::GLITTER,
		&EnumLikeValue::SMOKE,
		&EnumLikeValue::SPARK
	}
);

EnumLike::EnumLike(std::initializer_list<EnumLikeValue*> Vals)
{
	Values = TMap<FString, EnumLikeValue*>();
	Names = TArray<FString>();
	Ids = TArray<FString>();
	for (EnumLikeValue* Value : Vals)
	{
		Values.Add(Value->Name, Value);
		Names.Add(Value->Name);
		Ids.Add(Value->Id);
		Value->SetParent(this);
	}
}

TArray<FString>* EnumLike::GetNames()
{
	return &Names;
}

EnumLikeValue* EnumLike::GetDefaultValue()
{
	return *Values.Find(Names[0]);
}

EnumLikeValue* EnumLike::Get(FString& Name)
{
	return *Values.Find(Name);
}
