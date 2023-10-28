// Fill out your copyright notice in the Description page of Project Settings.


#include "VioBPFL.h"

#include <Windows.ApplicationModel.Activation.h>

#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "Engine/SkeletalMeshSocket.h"

bool UVioBPFL::IsWithEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}

int32 UVioBPFL::AddAnimCompositeSectionHelper(UAnimMontage* TargetAnimMontage, FName InSectionName, float StartPos)
{
	return TargetAnimMontage->AddAnimCompositeSection(InSectionName, StartPos);
}

void UVioBPFL::PopulateMontageWithClips(UAnimMontage* TargetMontageInput, TArray<UAnimSequence*> ClipsInput,
										TArray<FName> SectionNamesInput, UAnimSequence* OverrideLastClipInput)
{
	if (TargetMontageInput)
	{
		if (SectionNamesInput.Num() == 0)
		{
			// Here you can provide a default option in case the user doesn't fill the SectionNamesInput
			// SectionNamesInput = {
			// 	FName(TEXT("Section0")),FName(TEXT("Section1")), FName(TEXT("Section2")), FName(TEXT("Section3")),
			// 	FName(TEXT("Section4"))
			// };
			UE_LOG(LogTemp, Error, TEXT("Process interrupted. No Section Names provided"));
			return;
		}
		

		if(OverrideLastClipInput != nullptr) {
			ClipsInput.Add(OverrideLastClipInput);
		}

		float MontageDuration = 0.0f;

		for (int32 i = 0; i < ClipsInput.Num(); ++i)
		{
			// Create a new anim segment
			FAnimSegment NewSegment;
		
			NewSegment.SetAnimReference(ClipsInput[i]);
			
			NewSegment.StartPos = MontageDuration;
			NewSegment.AnimEndTime = ClipsInput[i]->GetPlayLength();

			// Create a new slot animation track if it's the first segment
			if (TargetMontageInput->SlotAnimTracks.Num() == 0)
			{
				FSlotAnimationTrack SlotAnimTrack;
				TargetMontageInput->SlotAnimTracks.Add(SlotAnimTrack);
			}

			// Add the new anim segment to the first slot animation track
			TargetMontageInput->SlotAnimTracks[0].AnimTrack.AnimSegments.Add(NewSegment);

			// Add a new Montage section at the start of the inserted clip
			TargetMontageInput->AddAnimCompositeSection(SectionNamesInput[i], MontageDuration);
			
			// Update the montage duration for the next iteration
			MontageDuration += ClipsInput[i]->GetPlayLength();

		}

		FName NotifyTrackName = "Shoot";
		
		// Mark the modified montage as dirt to be later saved on disk
		TargetMontageInput->MarkPackageDirty();
	}
}


float UVioBPFL::GetPlayLenght(const UAnimSequenceBase* TargetAnimSequence)
{
	return TargetAnimSequence->GetPlayLength();
}

void UVioBPFL::SetMontageSkeleton(UAnimMontage* TargetAnimationAsset, USkeleton* NewSkeleton)
{
	TargetAnimationAsset->SetSkeleton(NewSkeleton);
}

void UVioBPFL::GetSectionStartAndEndTimeHelper(UAnimMontage* TargetAnimationAsset, const int32 SectionIndex,float& OutputStartTime,
	float& OutputEndTime)
{
	TargetAnimationAsset->GetSectionStartAndEndTime(SectionIndex, OutputStartTime, OutputEndTime);
}

void UVioBPFL::AddSocket(USkeleton* TargetSkeleton, const FName SocketName, const FName BoneName)
{
	USkeletalMeshSocket* NewSocket = NewObject<USkeletalMeshSocket>(TargetSkeleton);
	
	TargetSkeleton->Modify(); 
	NewSocket->SocketName =SocketName; 
	NewSocket->BoneName =BoneName; 
	TargetSkeleton->Sockets.Add(NewSocket);

	TargetSkeleton->MarkPackageDirty();
}


