// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphNode_Alias.h"

#include "DialogueNodeData_Alias.h"


UDialogueGraphNode_Alias::UDialogueGraphNode_Alias()
{
	NodeDataClass = UDialogueNodeData_Alias_In::StaticClass();
}

void UDialogueGraphNode_Alias_In::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("PinCategory_Default"), TEXT("In Query"));
}

void UDialogueGraphNode_Alias_Out::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("PinCategory_Default"), TEXT("Out Query"));
}

void UDialogueGraphNode_Alias_Out::InitializeNodeData()
{
	Super::InitializeNodeData();
	
}
