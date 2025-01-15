// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNode_Alias.h"
#include "EdGraph/EdGraph.h"
#include "DialogueGraph.generated.h"

class UDialogueGraphNode_Alias_In;
class UDialogueNodeData_Alias;



/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UDialogueGraph();
	TArray<const UDialogueGraphNode_Alias_In*> Aliases;
	FAliasCounter AliasCounter;

private:
	void HandleThisGraphModified(const FEdGraphEditAction &InEditAction);

public: // UEdGraphSchema
	virtual void AddNode(UEdGraphNode* NodeToAdd, bool bUserAction, bool bSelectNewNode) override;

};
