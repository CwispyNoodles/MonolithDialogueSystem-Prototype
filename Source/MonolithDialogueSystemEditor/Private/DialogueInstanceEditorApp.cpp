#include "DialogueInstanceEditorApp.h"

#include "DialogueInstance.h"
#include "DialogueInstanceAppMode.h"

void FDialogueInstanceEditorApp::InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InInitToolkitHost, UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);

	WorkingAsset = Cast<UDialogueInstance>(InObject);

	InitAssetEditor(
		InMode,
		InInitToolkitHost,
		TEXT("DialogueInstanceEditor"),
		FTabManager::FLayout::NullLayout,
		true, // Create Standalone Menu
		true, // Create Default Toolbar
		ObjectsToEdit
	);

	AddApplicationMode(TEXT("DialogueInstanceAppMode"), MakeShareable(new FDialogueInstanceAppMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogueInstanceAppMode"));
}

void FDialogueInstanceEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}
