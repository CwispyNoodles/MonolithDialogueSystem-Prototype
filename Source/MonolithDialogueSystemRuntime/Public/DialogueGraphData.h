// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeData_Alias.h"
#include "UObject/Object.h"
#include "DialogueGraphData.generated.h"

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueGraphData : public UObject
{
	GENERATED_BODY()

public:
	FAliasCounter AliasCounter;

	UPROPERTY()
	TMap<FString, UDialogueNodeData_Alias_Out*> AliasToOutputMap;
};
