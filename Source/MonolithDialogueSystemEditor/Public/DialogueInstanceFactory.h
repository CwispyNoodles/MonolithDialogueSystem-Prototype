// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "DialogueInstanceFactory.generated.h"

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueInstanceFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogueInstanceFactory(const FObjectInitializer& InObjectInitializer);

public: // UFactory Interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
