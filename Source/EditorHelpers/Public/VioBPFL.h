// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VioBPFL.generated.h"

/**
 * 
 */
UCLASS()
class EDITORHELPERS_API UVioBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="EditorHelpers")
	static bool IsWithEditor();

	UFUNCTION(BlueprintCallable, Category="EditorHelpers|AnimationMontageHelpers")
	static int32 AddAnimCompositeSectionHelper(UAnimMontage* TargetAnimMontage, FName InSectionName, float StartPos);

	UFUNCTION(BlueprintCallable, Category="EditorHelpers|AnimationMontageHelpers",
		meta = (AutoCreateRefTerm="SectionNamesInput, ReloadingAnimSequenceInput"))
	static void PopulateMontageWithClips(UAnimMontage* TargetMontageInput, const TArray<UAnimSequence*> ClipsInput,
	                                     TArray<FName> SectionNamesInput, UAnimSequence* ReloadingAnimSequenceInput,
	                                     TSubclassOf<UAnimNotify> ShootNotifyToAdd);

	UFUNCTION(BlueprintPure, Category="EditorHelpers|AnimationMontageHelpers")
	static float GetPlayLenght(const UAnimSequenceBase* TargetAnimSequence);

	UFUNCTION(BlueprintCallable, Category="EditorHelpers|AnimationMontageHelpers")
	static void SetMontageSkeleton(UAnimMontage* TargetAnimationAsset, USkeleton* NewSkeleton);

	UFUNCTION(BlueprintCallable, Category="EditorHelpers|AnimationMontageHelpers")
	static void GetSectionStartAndEndTimeHelper(UAnimMontage* TargetAnimationAsset, const int32 SectionIndex,
	                                            float& OutputStartTime, float& OutputEndTime);

	UFUNCTION(BlueprintCallable, Category="EditorHelpers|Skeleton")
	static void AddSocket(USkeleton* TargetSkeleton, const FName SocketName, const FName BoneName);
};
