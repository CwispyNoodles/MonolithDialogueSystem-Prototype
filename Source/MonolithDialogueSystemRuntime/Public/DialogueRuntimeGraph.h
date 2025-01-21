// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueRuntimeGraph.generated.h"

class UDialogueGraphData;
class UDialogueNodeData_Base;

UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueRuntimePin : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName PinName;

	UPROPERTY()
	FGuid PinId;

	UPROPERTY()
	UDialogueRuntimePin* Connection = nullptr;

	UPROPERTY()
	class UDialogueRuntimeNode* Parent = nullptr;
};

UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueRuntimeNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UDialogueRuntimePin*> Pins;

	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	UDialogueNodeData_Base* NodeData = nullptr;
};

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueRuntimeGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDialogueGraphData* GraphData = nullptr;

	UPROPERTY()
	TArray<UDialogueRuntimeNode*> Nodes;
};
