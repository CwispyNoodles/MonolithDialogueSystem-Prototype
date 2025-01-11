// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

/**
 * 
 */
class FDialogueGraphPanelNodeFactory : public FGraphPanelNodeFactory 
{
 virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};
