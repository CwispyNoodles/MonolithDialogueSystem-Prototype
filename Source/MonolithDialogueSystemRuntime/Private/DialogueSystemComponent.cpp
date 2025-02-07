﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystemComponent.h"

#include "DialogueInstance.h"
#include "DialogueNodeData_Alias.h"
#include "DialogueNodeData_Dialogue.h"


// Sets default values for this component's properties
UDialogueSystemComponent::UDialogueSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

FDialogueText UDialogueSystemComponent::GetQueryAndResponse(int InIndex, bool& bFoundNewNode)
{
	bFoundNewNode = false;
	FDialogueText DialogueText;
	if (!CurrentNode)
	{
		return DialogueText;
	}
	
	if (CurrentNode->OutputPins.IsValidIndex(InIndex))
	{
		UDialogueRuntimePin* Pin = CurrentNode->OutputPins[InIndex];

		UDialogueRuntimePin* Connection = Pin->Connection;
		if (!Connection)
			return DialogueText;

		UDialogueRuntimeNode* ConnectionParent = Connection->Parent;
		if (!ConnectionParent)
			return DialogueText;

		if (UDialogueNodeData_Alias_In* AliasData = Cast<UDialogueNodeData_Alias_In>(ConnectionParent->NodeData))
		{
			if (UDialogueRuntimeNode* AliasOut = Dialogue->Graph->AliasToOutputMap[AliasData->AliasName.ToString()])
			{
				CurrentNode = AliasOut;
				DialogueText = GetQueryAndResponse(0, bFoundNewNode);
			}
		}
		
		if (UDialogueNodeData_Query* QueryData = Cast<UDialogueNodeData_Query>(ConnectionParent->NodeData))
		{
			DialogueText.QueryText = QueryData->QueryText;

			for (UDialogueRuntimePin* QueryPin : ConnectionParent->OutputPins)
			{
				if (QueryPin->Direction == EGPD_Output)
				{
					Connection = QueryPin->Connection;
					if (Connection)
					{
						ConnectionParent = Connection->Parent;
						CurrentNode = ConnectionParent;
						if (ConnectionParent)
						{
							if (UDialogueNodeData_Response* ResponseData = Cast<UDialogueNodeData_Response>(ConnectionParent->NodeData))
							{
								bFoundNewNode = true;
								DialogueText.ResponseTexts = ResponseData->ResponseTexts;
							}
						}
					}
				}
			}
		}
	}

	return DialogueText;

}

FDialogueText UDialogueSystemComponent::StartDialogue()
{
	if (!Dialogue)
	{
		return FDialogueText();
	}

	UDialogueRuntimeGraph* Graph = Dialogue->Graph;
	CurrentNode = Graph->RootNode;

	bool bSuccess;
	return GetQueryAndResponse(0, bSuccess);
	
}


// Called when the game starts
void UDialogueSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDialogueSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

