// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNode_Dialogue.h"
#include "DialogueGraphNode_Query.generated.h"

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Query : public UDialogueGraphNode_Dialogue
{
	GENERATED_BODY()

public:
	UDialogueGraphNode_Query();
	virtual EDialogueNodeType GetDialogueNodeType() override { return EDialogueNodeType::Query; }

public: // UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Query"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void AllocateDefaultPins() override;
};
