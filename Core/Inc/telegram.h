/*
 * Ethernet.h
 *
 *  Created on: Jul 23, 2022
 *      Author: Usman
 */

#ifndef INC_TELEGRAM_H_
#define INC_TELEGRAM_H_


typedef enum
{
	DHCP_OFF=0,
    DHCP_START,
    DHCP_WAIT_ADDRESS,
    DHCP_ADDRESS_ASSIGNED,
    DHCP_TIMEOUT,
    DHCP_LINK_DOWN

}DHCPStatusTypeEnum;

typedef struct
{
	uint8_t IPMode; //0: static (default), 1 : DHCP,
	uint8_t IPAddress[4];
	uint8_t Subnetmask[4];
	uint8_t Gateway[4];

	uint8_t ServerIP[4];
	uint16_t ServerPort;
	uint8_t ServerStatus;

	uint8_t MACAddress[6];
	uint8_t HasConfig;

	uint32_t DHCPTimer;
	DHCPStatusTypeEnum DHCP_State;

	uint8_t	NTP_Update;
	uint32_t NTP_RoundTrip;

	uint8_t RX_Buffer[1500];
	uint8_t TX_Buffer[1024];
	uint8_t HasData;


	uint8_t DHCPIPTxt[20];
	uint8_t DHCPSubnetTxt[20];
	uint8_t DHCPGatewayTxt[20];

	uint8_t SendDHCPIP;
	uint8_t DHCPFlag;

	uint8_t LinkStatus;
	uint8_t LinkSetupUp;

	uint32_t ThreadCounter;
	uint8_t ThreadHang;

	uint32_t PingTimer;
	uint8_t SendPing;

}EthernetTypedef;

typedef struct
{
	struct netconn *netconn;
	struct netbuf *netconnbuf;
	uint8_t status;
	int rc;

	uint16_t buflen;
	char* buf;


//	int sock;
//	int newcon;
//	int size;
//
//	struct sockaddr_in address;
//	struct sockaddr_in remoteaddress;


}NetconnTypeDef;

typedef struct
{
	uint8_t Text[50];
}TextTypedef;

typedef struct
{
	uint8_t Token[64];
	int32_t ChatID;

	uint8_t SendMsg[128];
	uint8_t SendFlag;
	uint8_t ReceiveMsg[128];
	uint8_t ReceiveFlag;

	uint8_t ServerStatus;
	uint32_t UpdateID;

	TextTypedef MessageList[200];
	uint8_t MessageType[200];
	uint16_t MessageCounter;

}TelegramTypeDef;

typedef struct
{
	TextTypedef StatsString[2];
}StringDef;

typedef struct
{
	uint8_t Lamp[3];
	uint16_t ThermostatsVal;
}DeviceStateTypedef;

/*Static IP ADDRESS*/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10

/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1



#define SERVER_PORT "443"
#define SERVER_NAME "api.telegram.org"

extern EthernetTypedef Ethernet;
extern TelegramTypeDef Telegram;
extern uint8_t WaitForTouchGFX;
extern uint8_t EnterKey;
extern uint16_t MessageIndex;
extern StringDef Description;
extern DeviceStateTypedef Device;

uint8_t comparestring(uint8_t *string1, uint8_t *string2,int size);

#endif /* INC_TELEGRAM_H_ */
