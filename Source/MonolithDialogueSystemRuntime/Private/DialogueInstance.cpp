// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstance.h"

void UDialogueInstance::PreSave(const ITargetPlatform* TargetPlatform)
{
	if (OnPreSaveListener)
	{
		OnPreSaveListener();
	}
}
