// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/FileHelper.h"

FString& UFileHelper::GetDisplaysContentPath()
{
	return DisplaysContentPath;
}

void UFileHelper::ListFilesInDir(FString Path, TArray<FString>& Result)
{
	IFileManager::Get().FindFiles(Result, *Path);
}
