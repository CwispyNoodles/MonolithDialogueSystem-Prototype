// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceEditor.h"

#define LOCTEXT_NAMESPACE "AssetEditor_GenericGraph"

FName FDialogueInstanceEditor::GetToolkitFName() const
{
	return FName("FDialogueInstanceEditor");
}

FText FDialogueInstanceEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Dialogue Instance Editor");
}

FString FDialogueInstanceEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("DialogueInstanceEditor");
}

FLinearColor FDialogueInstanceEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FDialogueInstanceEditor::GetDocumentationLink() const
{
	return TEXT("https://github.com/CwispyNoodles/MonolithDialogueSystem-v1");
}

void FDialogueInstanceEditor::OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit)
{
	
}

void FDialogueInstanceEditor::OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit)
{
	
}

#undef LOCTEXT_NAMESPACE