// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphNode_Response.h"

#include "DialogueNodeData_Dialogue.h"

UDialogueGraphNode_Response::UDialogueGraphNode_Response()
{
	NodeDataClass = UDialogueNodeData_Response::StaticClass();
}

void UDialogueGraphNode_Response::SyncPinsWithResponses()
{
	UDialogueNodeData_Response* NodeData = Cast<UDialogueNodeData_Response>(GetDialogueNodeData());

	int NumPins = Pins.Num() - 1;
	int NumResponses = NodeData->ResponseTexts.Num();

	while (NumPins > NumResponses)
	{
		RemovePinAt(NumPins - 1, EGPD_Output);
		NumPins--;
	}
	while (NumResponses > NumPins)
	{
		CreatePin(EGPD_Output, TEXT("Output"), TEXT(""));
		NumPins++;
	}
	
}

UDialogueNodeData_Response* UDialogueGraphNode_Response::GetResponseNodeData()
{
	return Cast<UDialogueNodeData_Response>(GetDialogueNodeData());
}

void UDialogueGraphNode_Response::AllocateDefaultPins()
{
	DefaultInputPin = CreatePin(EGPD_Input, TEXT("PinCategory_Default"), TEXT("Response In"));
	// CreatePin(EGPD_Output, TEXT("PinCategory_Default"), TEXT("Response Out"));
}
