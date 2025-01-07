// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include  "EdGraph/EdGraphNode.h"
#include "DialogueNode.generated.h"

class UDialogueNodeInfo;

UCLASS()
class UDialogueNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name);

	void SetNodeInfo(UDialogueNodeInfo* InNodeInfo) { NodeInfo = InNodeInfo; }
	UDialogueNodeInfo* GetNodeInfo() { return NodeInfo; }

protected:
	UPROPERTY()
	UDialogueNodeInfo* NodeInfo = nullptr;
};
