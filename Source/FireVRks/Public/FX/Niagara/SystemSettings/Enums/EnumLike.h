#pragma once
#include "EnumLikeValue.h"

/**
 * A enum-like type implementation that is more in line with the parameters system
 */
class EnumLike
{
	TMap<FString, EnumLikeValue*> Values;
	TArray<FString> Ids;
	TArray<FString> Names;
	
public:
	static EnumLike BURST_SHAPE;
	static EnumLike COLOR_EFFECT;
	static EnumLike SOS_SHAPE;
	static EnumLike EFFECT_ROTATION_SETTING;
	static EnumLike SOS_DELAY_TYPE;
	static EnumLike MOTION_TYPE;

	static EnumLike ARRAY_TRAVERSAL_MODE;
	
	explicit EnumLike(std::initializer_list<EnumLikeValue*> Vals);

	TArray<FString>* GetNames();

	EnumLikeValue* GetDefaultValue();

	EnumLikeValue* Get(FString& Name);
};
