# STM32 TELEGRAM BOT

This video show how to use telegram bot API to communicate with IoT device, in this case STM32.
STM32 connec to internet with ethernet/LAN. Telegram bot API run on https protocol (secure HTTP), so it jus GET and POST command run on secure layer (TLS)
STM32 running FreeRTOS, TouchGFX, LWIP and MbedTLS.

Demo video https://www.youtube.com/watch?v=UC3c98ec5t8

Please change Telegram token and chat ID with yourown fromm Telegram_Init function:
sprintf((char*)Telegram.Token,"CHANGE WITH YOUT TOKEN");
Telegram.ChatID = 0;//changewithyourchatID;
Executeable in hex format (STM32_TelegramBot_Ethernet.hex), with no Token and Chat ID.
When download, please enable external loader N25Q128A_STM32F746G-DISCO, from your STM32CubeProgrammer or STM32CubeIDE
