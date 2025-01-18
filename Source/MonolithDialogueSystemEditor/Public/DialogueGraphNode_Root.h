// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNode_Base.h"
#include "DialogueGraphNode_Root.generated.h"

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Root : public UDialogueGraphNode_Base
{
	GENERATED_BODY()

public: // UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Start"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Red); }
	virtual bool CanUserDeleteNode() const override { return false; }
	virtual void AllocateDefaultPins() override;
};
