// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstance.h"

#include "UObject/ObjectSaveContext.h"

void UDialogueInstance::PreSave(FObjectPreSaveContext saveContext)
{
	if (OnPreSaveListener)
	{
		OnPreSaveListener();
	}
}
