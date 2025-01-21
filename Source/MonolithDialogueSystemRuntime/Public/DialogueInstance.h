// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.h"
#include "UObject/Object.h"
#include "DialogueInstance.generated.h"

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueInstance : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;
};
