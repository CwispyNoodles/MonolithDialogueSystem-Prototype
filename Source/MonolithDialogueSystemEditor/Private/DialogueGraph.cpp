// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraph.h"

#include "DialogueGraphNode_Alias.h"
#include "GraphEditAction.h"

UDialogueGraph::UDialogueGraph()
{
	AddOnGraphChangedHandler(FOnGraphChanged::FDelegate::CreateUObject(this, &UDialogueGraph::HandleThisGraphModified));
}

void UDialogueGraph::HandleThisGraphModified(const FEdGraphEditAction& InEditAction)
{
	if (InEditAction.Action == GRAPHACTION_RemoveNode)
	{
		for (const UEdGraphNode* RemovedNode : InEditAction.Nodes)
		{
			if (const UDialogueGraphNode_Alias_In* AliasNode = Cast<UDialogueGraphNode_Alias_In>(RemovedNode))
			{
				UE_LOG(LogTemp, Warning, TEXT("Alias Node Destroyed"))
			}
		}
		
	}
}

void UDialogueGraph::AddNode(UEdGraphNode* NodeToAdd, bool bUserAction, bool bSelectNewNode)
{
	Super::AddNode(NodeToAdd, bUserAction, bSelectNewNode);

	if (NodeToAdd->IsA(UDialogueGraphNode_Alias_In::StaticClass()))
	{
		
	}
}

