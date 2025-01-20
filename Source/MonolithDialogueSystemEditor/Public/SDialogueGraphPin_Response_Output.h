// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"

/**
 * 
 */
class SDialogueGraphPin_Response_Output : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin_Response_Output)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
	FText GetResponseText() const;

	TSharedPtr<STextBlock> ResponseText;

protected:
	virtual FSlateColor GetPinColor() const override {
		return FSlateColor(FLinearColor::White);
	}
};
