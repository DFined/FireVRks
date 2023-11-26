#include "Util/DFU.h"

template <class SRC, typename RES>
RES DFU::IfNotNullMapElse(SRC* Src, RES DefaultValue, RES (* Mapper)(SRC*))
{
	if (Src == nullptr) return DefaultValue;
	return Mapper(Src);
}


FString DFU::ZStr(FString in, FString Padding, int len)
{
	FString Res = in;
	for (int i = in.Len(); i < len; i++)
	{
		Res = Padding + Res;
	}
	return Res;
}

FString DFU::AStr(FString in, FString Padding, int len)
{
	FString Res = in;
	for (int i = in.Len(); i < len; i++)
	{
		Res = Res + Padding;
	}
	return Res;
}

FString DFU::SecondsToTimeCode(float SecondsIn)
{
	auto Minutes = ((int)SecondsIn) / 60;
	auto Seconds = ((int)SecondsIn) % 60;
	auto DeciSeconds = (int)((SecondsIn - ((int)SecondsIn)) * 100);

	return ZStr(FString::FromInt(Minutes), "0", 2) + ":" + ZStr(FString::FromInt(Seconds), "0", 2) + "." + AStr(FString::FromInt(DeciSeconds), "0", 2);
}
