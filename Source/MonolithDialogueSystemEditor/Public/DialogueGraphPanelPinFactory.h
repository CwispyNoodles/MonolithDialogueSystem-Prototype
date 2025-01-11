// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphPanelNodeFactory.h"
#include "SGraphPin.h"

/**
 * 
 */
class SDialogueGraphPin : public SGraphPin
{
public:
 SLATE_BEGIN_ARGS(SDialogueGraphPin) {}
 SLATE_END_ARGS()

 void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj) {
  SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
 }

protected:
 virtual FSlateColor GetPinColor() const override {
  return FSlateColor(FLinearColor::White);
 }
};

struct FDialogueGraphPanelPinFactory : public FGraphPanelPinFactory {
public:
 virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;

};