#pragma once

/**
 * DFined util class
 */
class DFU
{
public:
	template <class SRC, typename RES>
	static RES IfNotNullMapElse(SRC* Src, RES DefaultValue, RES (*Mapper)(SRC*));

	static FString ZStr(FString In, FString Padding, int Len);

	static FString AStr(FString In, FString Padding, int Len);

	static FString SecondsToTimeCode(float SecondsIn);

	template <class KeyType, class ValType>
	static void GetValues(TMap<KeyType, ValType> Map, TArray<ValType>& ResultArray)
	{
		TArray<KeyType> Keys = TArray<KeyType>();
		Map.GetKeys(Keys);
		for (KeyType Key : Keys)
		{
			ResultArray.Add(*Map.Find(Key));
		}
	}
};
