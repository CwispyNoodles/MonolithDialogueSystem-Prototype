// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeData_Base.h"
#include "DialogueNodeData_Dialogue.generated.h"

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueNodeData_Query : public UDialogueNodeData_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(MultiLine))
	FText QueryText;
};

UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueNodeData_Response : public UDialogueNodeData_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(MultiLine))
	TArray<FText> ResponseTexts;
};
