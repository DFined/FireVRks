#include "FX/Niagara/v2/System/EffectSystemManager.h"

#include "FX/Niagara/v2/System/DefaultParameterSystem.h"
#include "FX/Niagara/v2/System/EffectSystem.h"
#include "Util/FileHelper.h"


void UEffectSystemManager::Init()
{
	Effects = TMap<FDFId, UEffectSystem*>();
	Effects.Empty();
	DEFAULT_EFFECT = UDefaultParameterSystem::Make();
	Register(DEFAULT_EFFECT);
	SystemInEditing = UCustomEffectSystem::Instance(this);

	TraverseAndLoadSystems();
}

void UEffectSystemManager::Register(UEffectSystem* System)
{
	Effects.Add(System->GetId(), System);
}

UDefaultParameterSystem* UEffectSystemManager::GetDefaultEffect() const
{
	return DEFAULT_EFFECT;
}

UEffectSystemManager* UEffectSystemManager::Instance()
{
	auto Manager = UDFStatics::New<UEffectSystemManager>();
	Manager->Init();
	return Manager;
}

UEffectSystem* UEffectSystemManager::Get(FDFId Id)
{
	if (auto Res = Effects.Find(Id))
	{
		return *Res;
	}
	return nullptr;
}

void UEffectSystemManager::List(TArray<UEffectSystem*>& Systems)
{
	TArray<FDFId> Ids = TArray<FDFId>();
	Effects.GetKeys(Ids);
	for (auto Id : Ids)
	{
		Systems.Add(*Effects.Find(Id));
	}
}

UCustomEffectSystem* UEffectSystemManager::GetSystemInEditing() const
{
	return SystemInEditing;
}

void UEffectSystemManager::LoadSystem(FString Path)
{
	//Deserialization in unreal is a pain: first we read the string, then we parse it to a FJsonObject, then we parse that to the actual object
	FString JsonString = FString();
	FString Ignored = FString();
	FString Filename = FString();
	FPaths::Split(Path, Ignored, Filename, Ignored);
	FFileHelper::LoadFileToString(JsonString, *UFileHelper::GetInstance()->SystemPath(Path));

	TSharedPtr<FJsonObject> SystemJsonObj = MakeShareable(new FJsonObject());
		
	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), SystemJsonObj);
	auto NewSystem = UCustomEffectSystem::FromJson(SystemJsonObj, this);
	auto IconFilename = Filename + ".png";
	auto IconPath = UFileHelper::GetInstance()->IconPath(IconFilename);
	NewSystem->SetIcon(UIcon::New(NewSystem, IconPath, false));
	Register(NewSystem);
}

void UEffectSystemManager::TraverseAndLoadSystems() 
{
	TArray<FString> SystemFilePaths = TArray<FString>();
	UFileHelper::GetInstance()->ListFilesInDir(UFileHelper::GetInstance()->GetSystemsContentPath(), SystemFilePaths);

	for (auto Path : SystemFilePaths)
	{
		LoadSystem(Path);
	}
}

void UEffectSystemManager::SaveEffect(UCustomEffectSystem* System)
{
	FString JsonSaveData;
	TSharedPtr<FJsonObject> SaveObj = System->ToJson();
	FJsonSerializer::Serialize(SaveObj.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonSaveData), true);

	FString DataPath = FPaths::Combine(UFileHelper::GetInstance()->GetSystemsContentPath(), System->GetId().GetId() + ".json");
	FFileHelper::SaveStringToFile(JsonSaveData, *DataPath);
}

void UEffectSystemManager::SetSystemInEditing(UCustomEffectSystem* bSystemInEditing)
{
	this->SystemInEditing = bSystemInEditing;
}
