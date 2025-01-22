// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueNodeData_Base.generated.h"

class UDialogueRuntimeNode;
/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueNodeData_Base : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDialogueRuntimeNode* Parent = nullptr;
};
