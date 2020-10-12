// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "../MHGameInstance.h"
#include "Components/TextBlock.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"


void ULobbyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	T_ChatInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("T_ChatInput")));

	if (T_ChatInput)
	{
		T_ChatInput->OnTextCommitted.AddDynamic(this, &ULobbyWidgetBase::ProcessTextCommited);
	}

	T_ChatOutput = Cast<UScrollBox>(GetWidgetFromName(TEXT("T_ChatOutput")));
}

void ULobbyWidgetBase::ProcessTextCommited(const FText & Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
	{
		if (Text.CompareToCaseIgnored(FText::GetEmpty())) // 엔터를 눌렀을때 메시지를 아무것도 안적었을경우 (공백일 경우)
		{
			//Local PC -> Host PC
			ALobbyPC* PC = GetOwningPlayer<ALobbyPC>();
			if (PC)
			{
				UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
				if (GI)
				{
					FString Temp = FString::Printf(TEXT("%s : %s"), *GI->GetUserNN(), *Text.ToString());

					PC->C2S_SendMessage(FText::FromString(Temp));
					T_ChatInput->SetText(FText::FromString(TEXT("")));
				}

			}
		}
	}
	break;
	case ETextCommit::OnCleared:
	{
		T_ChatInput->SetUserFocus(GetOwningPlayer());
	}
	break;
	}
}

void ULobbyWidgetBase::AddMessage(FText Message)
{
	if (T_ChatOutput)
	{
		UTextBlock* NewTextBlock = NewObject<UTextBlock>(T_ChatOutput);
		if (NewTextBlock)
		{
			NewTextBlock->SetText(Message);
			NewTextBlock->Font.Size = 30;
			T_ChatOutput->AddChild(NewTextBlock);
			T_ChatOutput->ScrollToEnd();
		}
	}
}
