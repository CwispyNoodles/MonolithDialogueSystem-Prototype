// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDialogueNodeEventSignature, UEdGraphNode*)

class UDialogueNodeData;
/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	void SetPosition(FVector2D InPos);
	virtual void OnPropertiesChanged() { GetGraph()->NotifyNodeChanged(this); }
	void SetDialogueNodeData(UDialogueNodeData* InNodeData) { DialogueNodeData = InNodeData; }
	UDialogueNodeData* GetDialogueNodeData() const { return DialogueNodeData; }
	virtual void InitializeNodeData();

protected:
	UPROPERTY()
	TSubclassOf<UDialogueNodeData> NodeDataClass;
	
	UPROPERTY()
	UDialogueNodeData* DialogueNodeData = nullptr;

public: // UEdGraphNode Interface
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	
};
