// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphNode_Dialogue.h"

#include "DialogueNodeData_Dialogue.h"

UDialogueGraphNode_Dialogue::UDialogueGraphNode_Dialogue()
{
	NodeDataClass = UDialogueNodeData_Dialogue::StaticClass();
}
