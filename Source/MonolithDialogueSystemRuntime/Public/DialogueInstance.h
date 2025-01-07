// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.h"
#include "UObject/Object.h"
#include <functional>
#include "DialogueInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueInstance : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString DialogueName = TEXT("Enter Dialogue Name Here");

	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;

	// Gets called everytime we save our asseta
	virtual void PreSave(const ITargetPlatform* TargetPlatform) override;

	void SetPreSaveListener(std::function<void()> InOnPreSaveListener) { OnPreSaveListener = InOnPreSaveListener; }

private:
	std::function<void()> OnPreSaveListener = nullptr;
};
