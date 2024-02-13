#pragma once

#define FROM_JSON(Ptr, Type, Outer) Type::FromJson(Ptr.Get(), Outer)
#define FROM_STRING(Str, Type, Outer) Type::FromString(Str, Outer)

class DFJsonUtil
{
public:
	template <class T>
	static T* GetObjectField(TSharedPtr<FJsonObject> Obj, FString Name, UObject* Outer)
	{
		auto ResObj = Obj->GetObjectField(Name);
		return FROM_JSON(ResObj, T, Outer);
	}

	template <class T>
	static void GetArrayField(TSharedPtr<FJsonObject> Obj, FString Name, UObject* Outer, TArray<T*>& TargetArray)
	{
		for(TSharedPtr<FJsonValue> MPtr : Obj->GetArrayField(Name))
		{
			TargetArray.Add(T::FromJson(MPtr->AsObject(), Outer));
		}
	}

	template <class Key, class Value>
	static void GetMapField(TSharedPtr<FJsonObject> Obj, FString Name, UObject* Outer, TMap<Key*, Value*>& TargetMap)
	{
		auto SubObject = Obj->GetObjectField(Name);
		for(auto Entry : SubObject->Values)
		{
			TargetMap.Add(FROM_STRING(Entry.Value, Value, Outer), FROM_JSON(Entry.Value, Key, Outer));
		}
	}

	
};
