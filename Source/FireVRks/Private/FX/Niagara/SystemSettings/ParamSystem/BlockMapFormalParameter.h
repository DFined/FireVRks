#pragma once
#include "FX/Niagara/SystemSettings/FormalParameter/BlockCompoundParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/FormalParameter.h"
#include "FX/Niagara/SystemSettings/FormalParameter/ValueEqualsPredicate.h"

template <class ValueType>
class BlockMapFormalParameter
{
	FormalParameter<ValueType> Discriminator;

public:
	TMap<ValueType, BlockCompoundParameter*> Options;

	BlockMapFormalParameter(const FormalParameter<ValueType>& Discriminator, const TMap<ValueType, BlockCompoundParameter*>& Options)
		: Discriminator(Discriminator),
		  Options(Options)
	{
	}

	void AddTo(BlockCompoundParameter* Parent)
	{
		TArray<ValueType> Keys = TArray<ValueType>();
		Options.GetKeys(Keys);
		Parent->AddChild(Discriminator);
		for (ValueType Val : Keys)
		{
			auto Param = *Options.Find(Val);
			Parent->AddChild(Param);
			Param->SetDisplayPredicate(ValueEqualsPredicate<ValueType>::Of(Discriminator, Val));
		}
	}
};
