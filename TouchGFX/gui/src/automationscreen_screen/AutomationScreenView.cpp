#include <gui/automationscreen_screen/AutomationScreenView.hpp>
#include <touchgfx/Color.hpp>
extern "C"
{
#include "global.h"
}

AutomationScreenView::AutomationScreenView()
{

}

void AutomationScreenView::setupScreen()
{
    AutomationScreenViewBase::setupScreen();
}

void AutomationScreenView::tearDownScreen()
{
    AutomationScreenViewBase::tearDownScreen();
}

void AutomationScreenView::handleTickEvent()
{
	if(Telegram.ReceiveFlag){
		Telegram_Command_Check();
		Telegram.ReceiveFlag=0;
	}
}

void AutomationScreenView::Switch1_Execute()
{
	if(Switch1.getState()){
		Lamp1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 1 Change State : ON");
	}
	else{
		Lamp1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 1 Change State : OFF");
	}

	Lamp1.invalidate();
	Telegram.SendFlag=1;
}

void AutomationScreenView::Switch2_Execute()
{
	if(Switch2.getState()){
		Lamp2Painter.setColor(touchgfx::Color::getColorFromRGB( 0, 255,0));
		sprintf((char*)Telegram.SendMsg,"Lamp 2 Change State : ON");
	}
	else{
		Lamp2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 2 Change State : OFF");
	}

	Lamp2.invalidate();
	Telegram.SendFlag=1;


}

void AutomationScreenView::Switch3_Execute()
{
	if(Switch3.getState()){
		Lamp3Painter.setColor(touchgfx::Color::getColorFromRGB(0,0,255));
		sprintf((char*)Telegram.SendMsg,"Lamp 3 Change State : ON");
	}
	else{
		Lamp3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 3 Change State : OFF");
	}

	Lamp3.invalidate();
	Telegram.SendFlag=1;


}

void AutomationScreenView::Thermostat_Change(int value)
{

	sprintf((char*)Telegram.SendMsg,"Thermostat setting change: %d",value);
	Telegram.SendFlag=1;
	Unicode::itoa(value,ThermostateValueTextBuffer ,THERMOSTATEVALUETEXT_SIZE, 10);
	ThermostateValueText.resizeToCurrentText();
	ThermostateValueText.invalidate();
	box1.invalidate();
}

void AutomationScreenView::Set_Device()
{
	if(Device.Lamp[0]){

	}
}

void AutomationScreenView::Telegram_Command_Check(void)
{

	uint16_t i,j,val;
	uint8_t bfr[8];

	if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/CommandList", strlen("/CommandList"))){
		sprintf((char*)Telegram.SendMsg,"Command List:\r\n"\
				"1. Set Lamp : /Lamp x ON/OFF, x = 1,2,3\r\n"\
				"2. Set Thermostat: /Thermostat val, val = 0-100\r\n"\
				"3. Get Status: /Status\r\n"\
				"4. Get Command List: /CommandList\r\n");
		Telegram.SendFlag=1;

	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Status", strlen("/Status"))){
		sprintf((char*)Telegram.SendMsg,"Status:\r\n"\
				"1. Lamp 1: %s\r\n"\
				"2. Lamp 2: %s\r\n"\
				"3. Lamp 3: %s\r\n"\
				"4. Thermostat: %d",Description.StatsString[Switch1.getState()].Text,Description.StatsString[Switch2.getState()].Text,
				Description.StatsString[Switch2.getState()].Text,slider1.getValue());

		Telegram.SendFlag=1;

	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Lamp 1 ON", strlen("/Lamp 1 ON"))){

		Lamp1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 1 ON");
	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Lamp 1 OFF", strlen("/Lamp 1 OFF"))){
		Lamp1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 1 OFF");
	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Lamp 2 ON", strlen("/Lamp 2 ON"))){
		Lamp2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 2 ON");
	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Lamp 2 OFF", strlen("/Lamp 2 OFF"))){
		Lamp2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 2 OFF");
	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Lamp 3 ON", strlen("/Lamp 3 ON"))){
		Lamp3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
		sprintf((char*)Telegram.SendMsg,"Lamp 3 ON");
	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Lamp 3 OFF", strlen("/Lamp 3 OFF"))){
		Lamp3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		sprintf((char*)Telegram.SendMsg,"Lamp 3 OFF");
	}
	else if(comparestring(Telegram.ReceiveMsg, (uint8_t*)"/Thermostat:", strlen("/Thermostat:"))){
		for(i=0;i<strlen((char*)Telegram.ReceiveMsg);i++){
			if(Telegram.ReceiveMsg[i]==':'){
				break;
			}
		}

		memset(bfr,0,8);
		for(j=i+1;j<strlen((char*)Telegram.ReceiveMsg)+i+1;j++){
		  bfr[j-i-1]=Telegram.ReceiveMsg[j];
		}
		val=atoi((char*)bfr);

		if(val<=100){
		Unicode::itoa(val, ThermostateValueTextBuffer, THERMOSTATEVALUETEXT_SIZE, 10);
		ThermostateValueText.resizeToCurrentText();
		ThermostateValueText.invalidate();
		slider1.setValue(val);
		slider1.invalidate();

		sprintf((char*)Telegram.SendMsg,"Set Thermostat to %d",val);
		}
		else{
			sprintf((char*)Telegram.SendMsg,"Invalid value");
		}
	}
	else{
		sprintf((char*)Telegram.SendMsg,"Invalid Command");
	}

	Telegram.SendFlag=1;
	Lamp1.invalidate();
	Lamp2.invalidate();
	Lamp3.invalidate();



}
