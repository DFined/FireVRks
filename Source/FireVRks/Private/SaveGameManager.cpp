// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameManager.h"

#include "Components/Spacer.h"
#include "DFUI/DFUI.h"
#include "Display/DisplayData.h"
#include "Display/DisplayManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/EDFUI.h"
#include "Util/DFJsonUtil.h"
#include "Util/FileHelper.h"
#include "World/Launcher/LauncherManager.h"

TSharedPtr<FJsonObject> USaveGameManager::ToJson()
{
	auto JsonObj = new FJsonObject();

	JsonObj->SetObjectField(DisplayFieldName, UDisplayManager::GetInstance()->GetDisplayInEditing()->ToJson());
	DFJsonUtil::SetArrayFieldFromMapValues(JsonObj, LaunchersFieldName, ULauncherManager::GetInstance()->GetArrays());

	return MakeShareable(JsonObj);
}

void USaveGameManager::DoLoadGame(FString Name, UObject* WCO)
{
	//Deserialization in unreal is a pain: first we read the string, then we parse it to a FJsonObject, then we parse that to the actual object
	FString JsonString = FString();
	FString Ignored = FString();
	FString Filename = FString();
	FFileHelper::LoadFileToString(JsonString, *UFileHelper::GetInstance()->DisplayPath(Name));

	TSharedPtr<FJsonObject> DisplayJsonObj = MakeShareable(new FJsonObject());
		
	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), DisplayJsonObj);

	auto DisplayManager = UDisplayManager::GetInstance();
	auto Display = UDisplayData::FromJson(DisplayManager, DisplayJsonObj->GetObjectField(DisplayFieldName));
	DisplayManager->SetDisplayInEditing(Display);

	auto LauncherManager = ULauncherManager::GetInstance();
	LauncherManager->Reset();
	auto LauncherData = DisplayJsonObj->GetArrayField(LaunchersFieldName);
	for (auto LauncherDatum : LauncherData)
	{
		UGenericLauncherArray::FromJson(LauncherDatum->AsObject(), WCO);
	}
}

void USaveGameManager::DoSaveGame(FString Name)
{
	auto SaveObj = ToJson();
	FString JsonSaveData;
	FJsonSerializer::Serialize(SaveObj.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonSaveData), true);

	FString DataPath = FPaths::Combine(UFileHelper::GetInstance()->GetDisplaysContentPath(), Name);
	FFileHelper::SaveStringToFile(JsonSaveData, *DataPath);
}

void USaveGameManager::ConfirmSave(UWidget* Widget)
{
	auto TextBlock = Cast<UTextBlock>(Widget);
	DoSaveGame(TextBlock->GetText().ToString());
}

void USaveGameManager::CheckSaveSlot(UWidget* Widget)
{
	auto TextBox = Cast<UEditableTextBox>(Widget);
	auto Name = TextBox->GetText().ToString() + ".json";
	TArray<FString> DisplayFilePaths = TArray<FString>();
	UFileHelper::GetInstance()->ListFilesInDir(UFileHelper::GetInstance()->GetDisplaysContentPath(), DisplayFilePaths);
	if(DisplayFilePaths.Contains(Name))
	{
		auto Ctrlr = UGameplayStatics::GetPlayerController(Widget->GetWorld(), 0);
		auto ConfirmationPopup = EDFUI::OpenInputPopup<UTextBlock>(Ctrlr, "The specified file already exists. Are you sure you want to overwrite it?");
		auto Text = ConfirmationPopup->GetWidget<UTextBlock>();
		Text->SetText(FText::FromString(Name));
		ConfirmationPopup->GetOnConfirm()->AddUniqueDynamic(this, &USaveGameManager::ConfirmSave);
	}
	DoSaveGame(Name);
}

void USaveGameManager::SaveGame(UWorld* World)
{
	auto Ctrlr = UGameplayStatics::GetPlayerController(World, 0);
	auto NamePopup = EDFUI::OpenInputPopup<UEditableTextBox>(Ctrlr, "Input a name for the save file");
	DFStyleUtil::TextBoxStyle(NamePopup->GetWidget<UEditableTextBox>());
	NamePopup->GetOnConfirm()->AddUniqueDynamic(this, &USaveGameManager::CheckSaveSlot);	
}

void USaveGameManager::ConfirmLoadGame(UWidget* Widget)
{
	DoLoadGame(Cast<UEditableTextBox>(Widget)->GetText().ToString(), Widget);
}

void USaveGameManager::LoadGame(UObject* WCO)
{
	auto World = WCO->GetWorld();
	auto Ctrlr = UGameplayStatics::GetPlayerController(World, 0);
	auto NamePopup = EDFUI::OpenInputPopup<UEditableTextBox>(Ctrlr, "Input filename to load");
	DFStyleUtil::TextBoxStyle(NamePopup->GetWidget<UEditableTextBox>());
	NamePopup->GetOnConfirm()->AddUniqueDynamic(this, &USaveGameManager::ConfirmLoadGame);
}
