#include <gui/chatscreen_screen/ChatscreenView.hpp>

extern "C"
{
#include "global.h"
}

ChatscreenView::ChatscreenView()
{

}

void ChatscreenView::setupScreen()
{
    ChatscreenViewBase::setupScreen();
    WaitForTouchGFX=1;
    Unicode::snprintf(StatustextArea1Buffer, STATUSTEXTAREA1_SIZE, "Ethernet cable unplugged");
	StatustextArea1.resizeToCurrentText();
	StatustextArea1.invalidate();
	box2_1.invalidate();
	keyboard.setPosition(0, 0, 320, 240);
	Keyboardcontainer.add(keyboard);

	MessagescrollList.setNumberOfItems(Telegram.MessageCounter);
	MessagescrollList.initialize();
	if(Telegram.MessageCounter)
	   MessagescrollList.animateToItem(Telegram.MessageCounter-1);

	//Lamp Status



}

void ChatscreenView::tearDownScreen()
{
    ChatscreenViewBase::tearDownScreen();
}

void ChatscreenView::handleTickEvent()
{
	Get_Status();
	if(EnterKey){
		Unicode::strncpy(EditTextflexButtonBuffer, keyboard.getBuffer(), EDITTEXTFLEXBUTTON_SIZE);
		EditTextflexButton.invalidate();
		KeyboardmodalWindow.setVisible(false);
		KeyboardmodalWindow.invalidate();
		EnterKey=0;
	}

	//Check Telegram message
	if(Telegram.ReceiveFlag){
		Telegram.ReceiveFlag=0;
		memcpy(Telegram.MessageList[Telegram.MessageCounter].Text,Telegram.ReceiveMsg, strlen((char*)Telegram.ReceiveMsg));
		Telegram.MessageType[Telegram.MessageCounter]=1;//receive
		Telegram.MessageCounter++;
		if(Telegram.MessageCounter>200){
			Telegram.MessageCounter=0;
			MessageIndex=0;
		}

		MessagescrollList.setNumberOfItems(Telegram.MessageCounter);
		MessagescrollList.initialize();
		MessagescrollList.animateToItem(Telegram.MessageCounter-1);

	}
}


void ChatscreenView::SendMessage_Execute()
{
	Unicode::toUTF8(EditTextflexButtonBuffer, Telegram.SendMsg, EDITTEXTFLEXBUTTON_SIZE);
	Unicode::toUTF8(EditTextflexButtonBuffer, Telegram.MessageList[Telegram.MessageCounter].Text, EDITTEXTFLEXBUTTON_SIZE);
	Telegram.MessageType[Telegram.MessageCounter]=0;//Send


	Unicode::snprintf(EditTextflexButtonBuffer, EDITTEXTFLEXBUTTON_SIZE, "");
	keyboard.setBuffer(EditTextflexButtonBuffer);
	EditTextflexButton.invalidate();

	if(strlen((char*)Telegram.SendMsg)>0){
		Telegram.MessageCounter++;
		if(Telegram.MessageCounter==200){
			Telegram.MessageCounter=0;
		}
		MessagescrollList.setNumberOfItems(Telegram.MessageCounter);
		MessagescrollList.initialize();
		 MessagescrollList.animateToItem(Telegram.MessageCounter-1);
		Telegram.SendFlag=1;

	}
}

void ChatscreenView::Get_Status()
{
	touchgfx::Unicode::UnicodeChar DHCPIP[20];

	if(Telegram.ServerStatus){
		Unicode::snprintf(TelegramStatustextAreaBuffer, TELEGRAMSTATUSTEXTAREA_SIZE, "Connected");
		TelegramStatustextArea.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
	}
	else{
		Unicode::snprintf(TelegramStatustextAreaBuffer, TELEGRAMSTATUSTEXTAREA_SIZE, "Disconnected");
		TelegramStatustextArea.setColor(touchgfx::Color::getColorFromRGB(255,0, 0));
	}

	TelegramStatustextArea.resizeToCurrentText();
	TelegramStatustextArea.invalidate();

	Unicode::strncpy(DHCPIP, (char*)Ethernet.DHCPIPTxt, 20);
	switch(Ethernet.DHCP_State){
	case DHCP_START:
		Unicode::snprintf(StatustextArea1Buffer, STATUSTEXTAREA1_SIZE, "DHCP Start, looking DHCP server...");
		break;
	case DHCP_WAIT_ADDRESS:
		Unicode::snprintf(StatustextArea1Buffer, STATUSTEXTAREA1_SIZE, "waiting IP address...");
		break;
	case DHCP_ADDRESS_ASSIGNED:
		Unicode::snprintf(StatustextArea1Buffer, STATUSTEXTAREA1_SIZE, "IP assigned %s",DHCPIP);
		break;
	case DHCP_LINK_DOWN:
		Unicode::snprintf(StatustextArea1Buffer, STATUSTEXTAREA1_SIZE, "Ethernet cable unplugged");
		break;
	}

	StatustextArea1.resizeToCurrentText();
	StatustextArea1.invalidate();
	box2_1.invalidate();
}

void ChatscreenView::MessagescrollListUpdateCenterItem(SelectedMessageContainer& item, int16_t itemIndex)
{
	item.AddItem(itemIndex);
}

void ChatscreenView::MessagescrollListUpdateItem(MessageContainer& item, int16_t itemIndex)
{
	item.AddItem(itemIndex);
}
