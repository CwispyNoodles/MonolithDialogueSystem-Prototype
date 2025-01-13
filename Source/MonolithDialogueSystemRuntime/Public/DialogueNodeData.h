// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueNodeData.generated.h"

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueNodeData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText NodeTitle = FText::FromString("Placeholder");
};
