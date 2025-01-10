// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphNode_Root.h"

void UDialogueGraphNode_Root::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("PinCategory_Default"), TEXT("In"));
}
