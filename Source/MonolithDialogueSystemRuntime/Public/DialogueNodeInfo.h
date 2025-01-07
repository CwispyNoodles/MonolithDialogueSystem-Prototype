// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfo.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueNodeInfo : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FText Title;

	UPROPERTY(EditAnywhere)
	FText DialogueText;

	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueResponses;
};
