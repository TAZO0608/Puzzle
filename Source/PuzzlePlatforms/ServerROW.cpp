// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerROW.h"
#include "Components/Button.h"

#include "MyUserWidget.h"

void UServerROW::Setup(class UMyUserWidget* InParent, uint32 InIndex)
 {
	Parent = InParent;
	Index = InIndex;
	RowButton->OnClicked.AddDynamic(this, &UServerROW::OnClicked);
	}

void UServerROW::OnClicked()
 {
	Parent->SelectIndex(Index);
	}



