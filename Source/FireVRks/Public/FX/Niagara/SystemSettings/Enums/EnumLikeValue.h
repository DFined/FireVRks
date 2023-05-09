#pragma once

class EnumLike;

class EnumLikeValue
{
public:
	FString Id;
	FString Name;

private:
	EnumLike* Parent;

public:

	EnumLikeValue(const FString Id, const FString Name);
	
	friend bool operator==(const EnumLikeValue& Lhs, const EnumLikeValue& RHS);

	friend bool operator!=(const EnumLikeValue& Lhs, const EnumLikeValue& RHS);

	EnumLike* GetParent() const;

public:
	void SetParent(EnumLike* Pnt);

	/**EFFECT SHAPES*/
	static EnumLikeValue PEONY;
	static EnumLikeValue BURST;
	static EnumLikeValue DISK;
	static EnumLikeValue RING;
	static EnumLikeValue CONE;
	static EnumLikeValue QUASAR;
	static EnumLikeValue MULTI_CONE;

	/**TRAIL TYPES*/
	static EnumLikeValue SMOKE;
	static EnumLikeValue SPARK;
	static EnumLikeValue CRACKLE;
	static EnumLikeValue GLITTER;
};
