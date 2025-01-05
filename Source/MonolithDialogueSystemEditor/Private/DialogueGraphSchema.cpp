// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphSchema.h"


UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D MouseLocation, bool bSelectNewNode)
{
	UEdGraphNode* Result = NewObject<UEdGraphNode>(ParentGraph);
	Result->NodePosX = MouseLocation.X;
	Result->NodePosY = MouseLocation.Y;

	Result->CreatePin
	(
		EGPD_Input,
		TEXT("Inputs"),
		TEXT("SomeInput")
	);

	Result->CreatePin
	(
		EGPD_Output,
		TEXT("Outputs"),
		TEXT("SomeOutput")
	);

	ParentGraph->Modify();
	ParentGraph->AddNode(Result, true, true);

	return Result;
	
}

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> NewNodeAction
	(
		new FNewNodeAction
		(
		FText::FromString(TEXT("Nodes")),
		FText::FromString(TEXT("New Node")),
		FText::FromString(TEXT("Makes a new node")),
		0
		)
	);

	ContextMenuBuilder.AddAction(NewNodeAction);
}
