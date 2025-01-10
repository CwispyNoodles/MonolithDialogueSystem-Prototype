// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphSchema.generated.h"

USTRUCT()
struct MONOLITHDIALOGUESYSTEMEDITOR_API FDialogueGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();
	
};
/**
 * 
 */
UCLASS(MinimalAPI)
class UDialogueGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public: // UEdGraphSchema Interface
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
};
