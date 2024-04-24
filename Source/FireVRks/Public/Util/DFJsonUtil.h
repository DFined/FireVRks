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
	static void GetArrayField(TSharedPtr<FJsonObject> Obj, FString Name, UObject* Outer)
	{
		for (TSharedPtr<FJsonValue> MPtr : Obj->GetArrayField(Name))
		{
			T::FromJson(MPtr->AsObject(), Outer);
		}
	}

	template <class T>
	static void GetArrayField(TSharedPtr<FJsonObject> Obj, FString Name, UObject* Outer, TArray<T*>& TargetArray)
	{
		for (TSharedPtr<FJsonValue> MPtr : Obj->GetArrayField(Name))
		{
			TargetArray.Add(T::FromJson(MPtr->AsObject(), Outer));
		}
	}

	template <class Key, class Value>
	static void GetMapField(TSharedPtr<FJsonObject> Obj, FString Name, UObject* Outer, TMap<Key*, Value*>& TargetMap)
	{
		auto SubObject = Obj->GetObjectField(Name);
		for (auto Entry : SubObject->Values)
		{
			TargetMap.Add(FROM_STRING(Entry.Value, Value, Outer), FROM_JSON(Entry.Value, Key, Outer));
		}
	}

	static void WriteVectorToJson(FJsonObject* Obj, FString Name, FVector Vector)
	{
		auto SubObj = new FJsonObject();
		SubObj->SetNumberField("X", Vector.X);
		SubObj->SetNumberField("Y", Vector.Y);
		SubObj->SetNumberField("Z", Vector.Z);

		Obj->SetObjectField(Name, MakeShareable(SubObj));
	}

	static void WriteRotatorToJson(FJsonObject* Obj, FString Name, FRotator Rotator)
	{
		auto SubObj = new FJsonObject();
		SubObj->SetNumberField("Roll", Rotator.Roll);
		SubObj->SetNumberField("Pitch", Rotator.Pitch);
		SubObj->SetNumberField("Yaw", Rotator.Yaw);

		Obj->SetObjectField(Name, MakeShareable(SubObj));
	}

	template <class T>
	static void SetArrayField(FJsonObject* Json, FString Name, TArray<T>& Array)
	{
		auto ValueArray = TArray<TSharedPtr<FJsonValue>>();
		for (auto Item : Array)
		{
			ValueArray.Add(MakeShareable(new FJsonValueObject(Item->ToJson())));
		}
		Json->SetArrayField(Name, ValueArray);
	}

	static FVector ReadVectorFromJson(TSharedPtr<FJsonObject> Json, FString Name);
	static FRotator ReadRotatorFromJson(TSharedPtr<FJsonObject> Json, FString Name);

	template <typename K, class V>
	static void SetArrayFieldFromMapValues(FJsonObject* Json, FString Name, TMap<K, V>& Array)
	{
		auto ValueArray = TArray<TSharedPtr<FJsonValue>>();
		for (auto Item : Array)
		{
			TSharedPtr<FJsonObject> JsonObject = Item.Value->ToJson();
			auto ValueObject = MakeShareable(new FJsonValueObject(JsonObject));
			ValueArray.Add(ValueObject);
		}
		Json->SetArrayField(Name, ValueArray);
	};
};
