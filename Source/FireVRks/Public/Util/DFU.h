#pragma once

/**
 * DFined util class
 */
class DFU
{
public:
	template <class SRC, typename RES>
	static RES IfNotNullMapElse(SRC* Src, RES DefaultValue, RES (*Mapper)(SRC*));

	static FString ZStr(FString in, FString Padding, int len)
	{
		FString Res = in;
		for (int i = in.Len(); i < len; i++)
		{
			Res = Padding + Res;
		}
		return Res;
	}
	
	static FString AStr(FString in, FString Padding, int len)
    	{
    		FString Res = in;
    		for (int i = in.Len(); i < len; i++)
    		{
    			Res = Res + Padding;
    		}
    		return Res;
    	}

	static FString SecondsToTimeCode(float SecondsIn)
	{
		auto Minutes = ((int)SecondsIn) / 60;
		auto Seconds = ((int)SecondsIn) % 60;
		auto DeciSeconds = (int)((SecondsIn - ((int)SecondsIn)) * 100);

		return ZStr(FString::FromInt(Minutes), "0", 2) + ":" + ZStr(FString::FromInt(Seconds), "0", 2) + "." + AStr(FString::FromInt(DeciSeconds), "0", 2);
	}
};
