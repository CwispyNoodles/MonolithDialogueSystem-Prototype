// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphNode_Alias.h"

#include "DialogueNodeData_Alias.h"

UDialogueGraphNode_Alias_In::UDialogueGraphNode_Alias_In()
{
	NodeDataClass = UDialogueNodeData_Alias_In::StaticClass();
}

void UDialogueGraphNode_Alias_In::AllocateDefaultPins()
{
	DefaultInputPin = CreatePin(EGPD_Input, TEXT("PinCategory_Default"), TEXT("In Query"));
}

UDialogueGraphNode_Alias_Out::UDialogueGraphNode_Alias_Out()
{
	NodeDataClass = UDialogueNodeData_Alias_Out::StaticClass();
}

UDialogueNodeData_Alias_Out* UDialogueGraphNode_Alias_Out::GetAliasOutData()
{
	return Cast<UDialogueNodeData_Alias_Out>(GetDialogueNodeData());
}

void UDialogueGraphNode_Alias_Out::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("PinCategory_Default"), TEXT("Out Query"));
}
