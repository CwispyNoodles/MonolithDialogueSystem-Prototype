// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphNode_Query.h"

void UDialogueGraphNode_Query::AllocateDefaultPins()
{
	DefaultInputPin = CreatePin(EGPD_Input, TEXT("PinCategory_Default"), TEXT("Query In"));
	CreatePin(EGPD_Output, TEXT("PinCategory_Default"), TEXT("Query Out"));
}
