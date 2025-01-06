// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.generated.h"

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
};

UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueRuntimeNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDialogueRuntimePin* InputPin = nullptr;
	
	UPROPERTY()
	TArray<UDialogueRuntimePin*> OutputPins;

	UPROPERTY()
	FVector2D Position;
	
};

UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueRuntimeGraph : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UDialogueRuntimeNode*> Nodes;
};
