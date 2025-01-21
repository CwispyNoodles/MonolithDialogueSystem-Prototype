// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNode_Dialogue.h"
#include "DialogueGraphNode_Response.generated.h"

class UDialogueNodeData_Response;
/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Response : public UDialogueGraphNode_Dialogue
{
	GENERATED_BODY()

public:
	UDialogueGraphNode_Response();
	void SyncPinsWithResponses();
	UDialogueNodeData_Response* GetResponseNodeData();
	virtual EDialogueNodeType GetDialogueNodeType() override { return EDialogueNodeType::Response; }

public: // UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Response"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void AllocateDefaultPins() override;
};
