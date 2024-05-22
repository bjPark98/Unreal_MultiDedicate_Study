// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "../Network/NetworkManager.h"
#include "../Network/PacketStream.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mLoginButton = Cast<UButton>(GetWidgetFromName(TEXT("LoginButton")));
	mIDText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ID")));
	mPasswordText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Password")));

	mLoginButton->OnClicked.AddDynamic(this, &ULoginWidget::LoginButtonClick);
}

void ULoginWidget::LoginButtonClick()
{
	FString	ID = mIDText->GetText().ToString();
	FString	Password = mPasswordText->GetText().ToString();

	uint8	Packet[1024] = {};

	CPacketStream	stream;

	stream.SetBuffer(Packet);

	int32	IDSize = ID.Len() * 2;
	int32	PassSize = Password.Len() * 2;

	stream.AddData<int>(&IDSize, 4);
	stream.AddData<TCHAR>(*ID, IDSize);

	stream.AddData<int>(&PassSize, 4);
	stream.AddData<TCHAR>(*Password, PassSize);

	int	StreamLength = stream.GetLength();

	CNetworkManager::GetInst()->Send(TEXT("LoginSession"), LPH_Login, 
		StreamLength, Packet);
}
