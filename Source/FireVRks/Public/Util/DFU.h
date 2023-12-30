#pragma once


/**
 * My static utils helper class
 */
#define DF_NEW(Class) public: \
 UFUNCTION(BlueprintCallable)\
  static Class* Instance(UObject* Outer) {\
   auto obj = NewObject<Class>(Outer); \
   return obj;\
  };

#define DF_NEW1(Class, type, name) public:\
 UFUNCTION(BlueprintCallable)\
 static Class* Instance(UObject* Outer, type name) {\
  auto obj = NewObject<Class>(Outer);\
   obj->Set##name(name);\
   return obj;\
 };

#define DF_NEW2(Class, type1, name1, type2, name2) public: \
 UFUNCTION(BlueprintCallable)\
 static Class* Instance(UObject* Outer, type1 name1, type2 name2) {\
  auto obj = NewObject<Class>(Outer);\
  obj->Set##name1(name1);\
  obj->Set##name2(name2);\
  return obj;\
 };

#define DF_NEW3(Class, type1, name1, type2, name2, type3, name3) public:\
 UFUNCTION(BlueprintCallable)\
 static Class* Instance(UObject* Outer, type1 name1, type2 name2, type3 name3) {\
  auto obj = NewObject<Class>(Outer);\
  obj->name1 = name1;\
  obj->name2 = name2;\
  obj->name3 = name3;\
  return obj;\
 };

#define DF_NEW4(Class, type1, name1, type2, name2, type3, name3, type4, name4) public:\
 UFUNCTION(BlueprintCallable)\
 static Class* Instance(UObject* Outer, type1 name1, type2 name2, type3 name3, type4 name4) {\
  auto obj = NewObject<Class>(Outer);\
  obj->name1 = name1;\
  obj->name2 = name2;\
  obj->name3 = name3;\
  obj->name4 = name4;\
 return obj;\
};

#define DF_NEW5(Class, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5) public:\
 UFUNCTION(BlueprintCallable)\
 static Class* Instance(UObject* Outer, type1 name1, type2 name2, type3 name3, type4 name4, type5 name5) {\
  auto obj = NewObject<Class>(Outer);\
  obj->name1 = name1;\
  obj->name2 = name2;\
  obj->name3 = name3;\
  obj->name4 = name4;\
  obj->name5 = name5;\
  return obj;\
 };

#define DF_NEW6(Class, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6) public:\
 UFUNCTION(BlueprintCallable)\
 static Class* Instance(UObject* Outer, type1 name1, type2 name2, type3 name3, type4 name4, type5 name5, type6 name6) {\
  auto obj = NewObject<Class>(Outer);\
  obj->name1 = name1;\
  obj->name2 = name2;\
  obj->name3 = name3;\
  obj->name4 = name4;\
  obj->name5 = name5;\
  obj->name6 = name6;\
  return obj;\
 };

#define DF_CHILD_MEMBER(Class, Name)\
 void Init##Name() {\
  this->Name = NewObject<Class>(this, Class::StaticClass());\
 }

#define GET_MAP_VALUES(Name, ValType, MapName)\
	TArray<ValType> Name = TArray<ValType>();\
	DFU::GetValues(MapName, Name);

class DFU
{
public:
	template <class SRC, typename RES>
	static RES IfNotNullMapElse(SRC* Src, RES DefaultValue, RES (*Mapper)(SRC*));

	static FString ZStr(FString In, FString Padding, int Len);

	static FString AStr(FString In, FString Padding, int Len);

	static FString SecondsToTimeCode(float SecondsIn);

	template <class KeyType, class ValType>
	static void GetValues(TMap<KeyType, ValType>& Map, TArray<ValType>& ResultArray)
	{
		TArray<KeyType> Keys = TArray<KeyType>();
		Map.GetKeys(Keys);
		for (KeyType Key : Keys)
		{
			ResultArray.Add(*Map.Find(Key));
		}
	}

	/**
	 * Search the outer chain for the first occurence of an object of the specified type
	 * @tparam T required object type
	 * @return the first object of the requested type in the outer chain, or null if its not found
	 */
	template <class T>
	static T* AttemptFindObjectByType(UObject* Start)
	{
		if (auto Obj = Cast<T>(Start))
		{
			return Obj;
		}
		if (auto Outer = Start->GetOuter())
		{
			return AttemptFindObjectByType<T>(Outer);
		}
		return nullptr;
	}
};
