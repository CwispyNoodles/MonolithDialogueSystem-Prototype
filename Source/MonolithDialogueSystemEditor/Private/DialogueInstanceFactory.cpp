// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceFactory.h"

#include "DialogueInstance.h"

UDialogueInstanceFactory::UDialogueInstanceFactory(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
	SupportedClass = UDialogueInstance::StaticClass();
}

UObject* UDialogueInstanceFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UDialogueInstance* DialogueInstance = NewObject<UDialogueInstance>(InParent, InName, Flags);
	return DialogueInstance;
}

bool UDialogueInstanceFactory::CanCreateNew() const
{
	return true;
}
