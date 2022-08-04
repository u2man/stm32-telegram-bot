# STM32 TELEGRAM BOT

This video show how to use telegram bot API to communicate with IoT device, in this case STM32.
STM32 connec to internet with ethernet/LAN. Telegram bot API run on https protocol (secure HTTP), so it jus GET and POST command run on secure layer (TLS)
STM32 running FreeRTOS, TouchGFX, LWIP and MbedTLS.

Demo video https://www.youtube.com/watch?v=UC3c98ec5t8

Please change Telegram token and chat ID with yourown
void Telegram_Init(void){
	//Set Telegram bot Token
	sprintf((char*)Telegram.Token,"CHANGE WITH YOUT TOKEN");
	//Set Chat ID
	Telegram.ChatID = 0;//changewithyourchatID;
	Telegram.ReceiveFlag=0;
	Telegram.SendFlag=0;
	Telegram.ServerStatus=0;
	Telegram.UpdateID=0;

	memset(Telegram.ReceiveMsg,0,sizeof(Telegram.ReceiveMsg));
	memset(Telegram.SendMsg,0,sizeof(Telegram.SendMsg));

	sprintf((char*)Description.StatsString[0].Text,"OFF");
	sprintf((char*)Description.StatsString[1].Text,"ON");

	Device.Lamp[0]=0;
	Device.Lamp[2]=1;
	Device.Lamp[0]=0;
	Device.ThermostatsVal=25;

}
 
