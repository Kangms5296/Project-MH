// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGM.h"

#include "../Battle/Character/Player/UserDataManager.h"
#include "../JsonHelper.h"

void ATitleGM::BeginPlay()
{
	UUserDataManager::Init();
	UJsonHelper::Init();
}
