// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstance.h"

#include "UObject/ObjectSaveContext.h"

UDialogueRuntimeNode* UDialogueInstance::GetFirstDialogueNode()
{
	if (!Graph)
		return nullptr;

	return nullptr;
}

void UDialogueInstance::PreSave(FObjectPreSaveContext saveContext)
{
	if (OnPreSaveListener)
	{
		OnPreSaveListener();
	}
}
