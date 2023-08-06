#pragma once

class EnumLike;

class EnumLikeValue
{
public:
	FString Id;
	FString Name;

private:
	EnumLike* Parent;
	int Ordinal;

public:

	EnumLikeValue(const FString Id, const FString Name, int bOrdinal);
	
	friend bool operator==(const EnumLikeValue& Lhs, const EnumLikeValue& RHS);

	friend bool operator!=(const EnumLikeValue& Lhs, const EnumLikeValue& RHS);

	EnumLike* GetParent() const;

public:
	void SetParent(EnumLike* Pnt);

	/**EFFECT SHAPES*/
	static EnumLikeValue PEONY;
	static EnumLikeValue BURST;
	static EnumLikeValue RING;
	static EnumLikeValue CONE;

	/**COLOR EFFECT TYPES*/
	static EnumLikeValue NO_EFFECT;
	static EnumLikeValue SIMPLE_COLOR_CHANGE;
	static EnumLikeValue FLARE;
	static EnumLikeValue COLOR_WAVE;
	static EnumLikeValue FLICKER;
	static EnumLikeValue ADVANCED_COLOR_LERP;

	/**SOS DISTRIBUTION TYPES*/
	static EnumLikeValue SOS_FROM_PARENT_PARTICLES;
	static EnumLikeValue SOS_SPHERE;
	static EnumLikeValue SOS_RING;

	/**EFFECT ROTATION SETTINGS*/
	static EnumLikeValue FIXED;
	static EnumLikeValue FROM_SHELL;
	static EnumLikeValue RANDOM;

	static EnumLikeValue SOS_DELAY_FROM_START;
	static EnumLikeValue SOS_DELAY_FROM_END;
	static EnumLikeValue SOS_DELAY_AT_REGULAR_INTERVAL;

	/**
	 * MOTION_TYPES
	 */
	static EnumLikeValue NO_MOTION;
	static EnumLikeValue FISH;
	static EnumLikeValue BEES;
	static EnumLikeValue WHEELS;
	static EnumLikeValue SPIRALS;
	static EnumLikeValue ADVANCED;

	/**
	 * LAUNCH ARRAY TRAVERSAL MODES
	 */
	static EnumLikeValue END_TO_END;
	static EnumLikeValue FROM_BOTH_ENDS;
	static EnumLikeValue FROM_CENTER;
	
	
	int GetOrdinal() const;
};
