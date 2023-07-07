#include "FX/Niagara/SystemSettings/Enums/EnumLike.h"

#include "FX/Niagara/SystemSettings/Enums/EnumLikeValue.h"

EnumLikeValue EnumLikeValue::PEONY = EnumLikeValue("PEONY", "Peony", 0);
EnumLikeValue EnumLikeValue::BURST = EnumLikeValue("BURST", "Burst", 1);
EnumLikeValue EnumLikeValue::RING = EnumLikeValue("RING", "Ring", 2);
EnumLikeValue EnumLikeValue::CONE = EnumLikeValue("CONE", "Cone", 3);

EnumLikeValue EnumLikeValue::NO_EFFECT = EnumLikeValue("NO_EFFECT", "No effect", 0);
EnumLikeValue EnumLikeValue::SIMPLE_COLOR_CHANGE = EnumLikeValue("SIMPLE_COLOR_CHANGE", "Simple color change", 1);
EnumLikeValue EnumLikeValue::FLARE = EnumLikeValue("FLARE", "Color flare", 2);
EnumLikeValue EnumLikeValue::FLICKER = EnumLikeValue("FLARE", "Color flicker", 3);
EnumLikeValue EnumLikeValue::COLOR_WAVE = EnumLikeValue("COLOR_WAVE", "Color wave", 4);
EnumLikeValue EnumLikeValue::ADVANCED_COLOR_LERP = EnumLikeValue("COLOR_WAVE", "Advanced color lerp", 5);

EnumLikeValue EnumLikeValue::SOS_FROM_PARENT_PARTICLES = EnumLikeValue("SOS_FROM_PARENT", "From parent effect", 0);
EnumLikeValue EnumLikeValue::SOS_SPHERE = EnumLikeValue("SOS_UNIFORM_SPHERE", "Sphere", 1);
EnumLikeValue EnumLikeValue::SOS_RING = EnumLikeValue("SOS_RING", "Ring", 2);

EnumLikeValue EnumLikeValue::FIXED = EnumLikeValue("FIXED", "Fixed", 0);
EnumLikeValue EnumLikeValue::FROM_SHELL = EnumLikeValue("FROM_SHELL", "From shell", 1);
EnumLikeValue EnumLikeValue::RANDOM = EnumLikeValue("RANDOM", "Randomized", 2);

EnumLikeValue EnumLikeValue::SOS_DELAY_FROM_START = EnumLikeValue("SOS_DELAY_FROM_START", "From start", 0);
EnumLikeValue EnumLikeValue::SOS_DELAY_FROM_END = EnumLikeValue("SOS_DELAY_FROM_END", "From end", 0);
EnumLikeValue EnumLikeValue::SOS_DELAY_AT_REGULAR_INTERVAL = EnumLikeValue("SOS_DELAY_AT_REGULAR_INTERVAL", "At regular interval", 0);

EnumLike EnumLike::BURST_SHAPE = EnumLike(
	{
		&EnumLikeValue::PEONY,
		&EnumLikeValue::BURST,
		&EnumLikeValue::RING,
		&EnumLikeValue::CONE
	}
);

EnumLike EnumLike::COLOR_EFFECT = EnumLike(
	{
		&EnumLikeValue::NO_EFFECT,
		&EnumLikeValue::SIMPLE_COLOR_CHANGE,
		&EnumLikeValue::FLARE,
		&EnumLikeValue::FLICKER,
		&EnumLikeValue::COLOR_WAVE,
		&EnumLikeValue::ADVANCED_COLOR_LERP
	}
);

EnumLike EnumLike::SOS_SHAPE = EnumLike(
	{
		&EnumLikeValue::SOS_FROM_PARENT_PARTICLES,
		&EnumLikeValue::SOS_SPHERE,
		&EnumLikeValue::SOS_RING
	}
);

EnumLike EnumLike::EFFECT_ROTATION_SETTING = EnumLike(
	{
		&EnumLikeValue::FIXED,
		&EnumLikeValue::FROM_SHELL,
		&EnumLikeValue::RANDOM
	}
);

EnumLike EnumLike::SOS_DELAY_TYPE = EnumLike(
	{
		&EnumLikeValue::SOS_DELAY_FROM_START,
		&EnumLikeValue::SOS_DELAY_FROM_END,
		&EnumLikeValue::SOS_DELAY_AT_REGULAR_INTERVAL,
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
