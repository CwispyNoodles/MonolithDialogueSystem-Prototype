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
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual void OnPropertiesChanged() { GetGraph()->NotifyNodeChanged(this); }
	void SetDialogueNodeData(UDialogueNodeData* InNodeData) { DialogueNodeData = InNodeData; }
	UDialogueNodeData* GetDialogueNodeData() const { return DialogueNodeData; }
	void InitializeNodeData();

	// UPROPERTY()
	// FDialogueNodeEventSignature OnPropertiesChangedDelegate;
	
	UPROPERTY()
	FText NodeTitle = FText::FromString("Placeholder");

protected:
	UPROPERTY()
	TSubclassOf<UDialogueNodeData> NodeDataClass;
	
	UPROPERTY()
	UDialogueNodeData* DialogueNodeData = nullptr;
	
};
