// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystemComponent.h"

#include "DialogueGraphData.h"
#include "DialogueInstance.h"
#include "DialogueNodeData_Dialogue.h"


// Sets default values for this component's properties
UDialogueSystemComponent::UDialogueSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

FDialogueText UDialogueSystemComponent::GetQueryAndResponse(int InIndex)
{
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
	
	return GetQueryAndResponse(0);

	

	// if (UDialogueRuntimeNode* Query = RootNode->Pins[0]->Parent)
	// {
	// 	// Assume for now that the next node will be a query node
	// 	UDialogueNodeData_Query* QueryData = Cast<UDialogueNodeData_Query>(Query->NodeData);
	// 	DialogueHandle.QueryText = QueryData->QueryText;
	//
	// 	if (UDialogueRuntimeNode* Responses = Query->Pins[1]->Parent)
	// 	{
	// 		UDialogueNodeData_Response* ResponseData = Cast<UDialogueNodeData_Response>(Responses->NodeData);
	// 		DialogueHandle.ResponseTexts = ResponseData->ResponseTexts;
	// 	}
	// 	
	// 	// if (Parent->NodeType == EDialogueNodeType::AliasIn)
	// 	// {
	// 	// 	WorkingDialogue->Graph->GraphData->AliasToOutputMap.Find(Parent->NodeData);
	// 	// }
	// }

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

