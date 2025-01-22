// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.h"
#include "UObject/Object.h"
#include "DialogueInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueInstance : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;

	void SetPreSaveListener(std::function<void()> InPreSaveListener) { OnPreSaveListener = InPreSaveListener; }
	virtual void PreSave(FObjectPreSaveContext saveContext) override;
	
private: // Members
	std::function<void()> OnPreSaveListener = nullptr;
};
