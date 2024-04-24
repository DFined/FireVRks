#include "World/Launcher/GenericLauncherArray.h"

#include "Util/DFJsonUtil.h"
#include "World/Launcher/LauncherData.h"
#include "World/Launcher/LauncherManager.h"

FString UGenericLauncherArray::GetArrayName() const
{
	return ArrayName;
}

void UGenericLauncherArray::SetArrayName(const FString& NewArrayName)
{
	this->ArrayName = NewArrayName;
}

void UGenericLauncherArray::AddLauncher(ULauncherData* Launcher)
{
	Launchers.Add(Launcher);
}

int UGenericLauncherArray::GetSize()
{
	return Launchers.Num();
}

TSharedPtr<FJsonObject> UGenericLauncherArray::ToJson()
{
	auto Obj = new FJsonObject();

	auto LaunchersArray = TArray<TSharedPtr<FJsonValue>>();
	for (auto Launcher : Launchers)
	{
		LaunchersArray.Add(MakeShareable(new FJsonValueObject(Launcher->ToJson())));
	}

	Obj->SetStringField("Name", ArrayName);
	Obj->SetArrayField("Launchers", LaunchersArray);
	return MakeShareable(Obj);
}

UGenericLauncherArray* UGenericLauncherArray::FromJson(TSharedPtr<FJsonObject> Json, UObject* WCO)
{
	auto Array = ULauncherManager::GetInstance()->CreateLauncherArray(Json->GetStringField("Name"));
	for (auto LauncherData : Json->GetArrayField("Launchers"))
	{
		ULauncherData::FromJson(LauncherData->AsObject(), Array->GetArrayName(), WCO);
	}
	return Array;
}
