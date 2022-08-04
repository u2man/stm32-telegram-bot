/*
 * Ethernet_Task.c
 *
 *  Created on: Jul 23, 2022
 *      Author: Usman
 */

#include "global.h"


const char TELEGRAM_CERTIFICATE_ROOT[] =
		"-----BEGIN CERTIFICATE-----\r\n" \
		"MIIDxTCCAq2gAwIBAgIBADANBgkqhkiG9w0BAQsFADCBgzELMAkGA1UEBhMCVVMx\r\n" \
		"EDAOBgNVBAgTB0FyaXpvbmExEzARBgNVBAcTClNjb3R0c2RhbGUxGjAYBgNVBAoT\r\n" \
		"EUdvRGFkZHkuY29tLCBJbmMuMTEwLwYDVQQDEyhHbyBEYWRkeSBSb290IENlcnRp\r\n" \
		"ZmljYXRlIEF1dGhvcml0eSAtIEcyMB4XDTA5MDkwMTAwMDAwMFoXDTM3MTIzMTIz\r\n" \
		"NTk1OVowgYMxCzAJBgNVBAYTAlVTMRAwDgYDVQQIEwdBcml6b25hMRMwEQYDVQQH\r\n" \
		"EwpTY290dHNkYWxlMRowGAYDVQQKExFHb0RhZGR5LmNvbSwgSW5jLjExMC8GA1UE\r\n" \
		"AxMoR28gRGFkZHkgUm9vdCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgLSBHMjCCASIw\r\n" \
		"DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL9xYgjx+lk09xvJGKP3gElY6SKD\r\n" \
		"E6bFIEMBO4Tx5oVJnyfq9oQbTqC023CYxzIBsQU+B07u9PpPL1kwIuerGVZr4oAH\r\n"\
		"/PMWdYA5UXvl+TW2dE6pjYIT5LY/qQOD+qK+ihVqf94Lw7YZFAXK6sOoBJQ7Rnwy\r\n" \
		"DfMAZiLIjWltNowRGLfTshxgtDj6AozO091GB94KPutdfMh8+7ArU6SSYmlRJQVh\r\n" \
		"GkSBjCypQ5Yj36w6gZoOKcUcqeldHraenjAKOc7xiID7S13MMuyFYkMlNAJWJwGR\r\n" \
		"tDtwKj9useiciAF9n9T521NtYJ2/LOdYq7hfRvzOxBsDPAnrSTFcaUaz4EcCAwEA\r\n" \
		"AaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYE\r\n" \
		"FDqahQcQZyi27/a9BUFuIMGU2g/eMA0GCSqGSIb3DQEBCwUAA4IBAQCZ21151fmX\r\n" \
		"WWcDYfF+OwYxdS2hII5PZYe096acvNjpL9DbWu7PdIxztDhC2gV7+AJ1uP2lsdeu\r\n" \
		"9tfeE8tTEH6KRtGX+rcuKxGrkLAngPnon1rpN5+r5N9ss4UXnT3ZJE95kTXWXwTr\r\n" \
		"gIOrmgIttRD02JDHBHNA7XIloKmf7J6raBKZV8aPEjoJpL1E/QYVN8Gb5DKj7Tjo\r\n" \
		"2GTzLH4U/ALqn83/B2gX2yKQOC16jdFU8WnjXzPKej17CuPKf1855eJ1usV2GDPO\r\n" \
		"LPAvTK33sefOT6jEm0pUBsV/fdUID+Ic/n4XuKxe9tQWskMJDE32p2u0mYRlynqI\r\n" \
		"4uJEvlz36hz1\r\n" \
		"-----END CERTIFICATE-----\r\n";
const size_t mbedtls_telegram_root_certificate_len = sizeof(TELEGRAM_CERTIFICATE_ROOT);

typedef struct
{
	uint8_t address[20];
	uint16_t port;
}Comm_Server_Struct;

EthernetTypedef Ethernet;
TelegramTypeDef Telegram;
#define MAX_DHCP_TRIES  4

static mbedtls_net_context server_fd;
static uint32_t flags;
static uint8_t buf[5000];
uint8_t TXBuffer[5000];
static const uint8_t *pers = (uint8_t *)("ssl_client");
static uint8_t vrfy_buf[1024];
static int ret;
uint8_t WaitForTouchGFX=0;
uint8_t EnterKey;
uint16_t MessageIndex=0;
StringDef Description;
DeviceStateTypedef Device;


void Telegram_Init(void);
uint8_t Connect_Tolegram(void);
uint8_t Telegram_Send_Message(void);
uint8_t Telegram_GetUpdate(void);
uint8_t SSL_Send_Data(void);
uint8_t SSL_Read_Data(void);


void TelegramParsingData(void);
void Telegram_Task(void const * argument){



	printf("LWIP Init\r\n");
	//TelegramParsingData();

	while(!WaitForTouchGFX){
		osDelay(1);
	}
	MX_LWIP_Init();
	Telegram_Init();
	Ethernet.DHCPFlag=0;
	for(;;){
		while(!Ethernet.DHCPFlag){
			printf("Waiting IP\r\n");
			osDelay(1000);
		}


		while(!Telegram.ServerStatus){
			Telegram.ServerStatus=Connect_Tolegram();
			osDelay(1000);
		}

		while(Telegram.ServerStatus){
			Telegram_Send_Message();
		Telegram.ServerStatus=Telegram_GetUpdate();
			osDelay(1000);
		}
		osDelay(100);

	}
}

uint8_t Telegram_GetUpdate(void){
	uint8_t Flag=0;

	sprintf((char*)buf,  "GET  https://api.telegram.org/bot%s/getUpdates?offset=%ld HTTP/1.1\r\n"\
	                        "Host:api.telegram.org\r\n"\
							"Content-Type: application/json\r\n\r\n",Telegram.Token,Telegram.UpdateID);

	printf("%s",buf);
	if(SSL_Send_Data()){
		Flag=SSL_Read_Data();
		if(Flag){
			TelegramParsingData();
		}
	}

	return Flag;

}

void TelegramParsingData(void){
	uint16_t i,j;
	uint8_t Valuebfr[128];
	uint32_t CurrentUpdateID;
	uint8_t Flag=0;

	printf("Message Parsing\r\n");
	for(i=0;i<strlen((char*)buf);i++){
		if(buf[i]=='{'){
			break;
		}
	}

	//Copy jason type
	memset(TXBuffer,0,sizeof(TXBuffer));
	memcpy(TXBuffer,&buf[i],strlen((char*)buf)-i);
	printf("JSON Data %s\r\n",TXBuffer);
	//Check Update ID
	memset(Valuebfr,0,sizeof(Valuebfr));
	for(i=0;i<strlen((char*)TXBuffer);i++){
		if(comparestring(&TXBuffer[i], (uint8_t*)"update_id", strlen((char*)"update_id"))){
			printf("found update id\r\n");
			for(j=i+11;j<strlen((char*)TXBuffer);j++){
				if(TXBuffer[j]==','){
					break;
				}
				Valuebfr[j-(i+11)]=TXBuffer[j];
				Flag=1;

			}
			break;
		}
	}
	CurrentUpdateID=atoi((char*)Valuebfr);
	//Text
	memset(Valuebfr,0,sizeof(Valuebfr));
	for(i=0;i<strlen((char*)TXBuffer);i++){
		if(comparestring(&TXBuffer[i], (uint8_t*)"text", strlen((char*)"text"))){
			for(j=i+7;j<strlen((char*)TXBuffer);j++){
				if(TXBuffer[j]=='"'){
					break;
				}
				Valuebfr[j-(i+7)]=TXBuffer[j];
			}
			break;
		}
	}

	printf("Update ID %lu %lu\r\n",CurrentUpdateID,Telegram.UpdateID);
	printf("Text %s\r\n",Valuebfr);

	if((Flag)&&(CurrentUpdateID!=Telegram.UpdateID-1)){

	//Copy to Telegram bufffer
	sprintf((char*)Telegram.ReceiveMsg, "%s",Valuebfr);
	Telegram.ReceiveFlag=1;
	Telegram.UpdateID=CurrentUpdateID+1;

	}

}

uint8_t Telegram_Send_Message(void){

	uint16_t MsgLength;
	uint8_t Flag=0;

	if(Telegram.SendFlag){
		Telegram.SendFlag=0;

	    sprintf((char*)TXBuffer,	"{\"chat_id\":\"%ld\",\"text\":\"%s\"}\r\n\r\n\r\n\r\n",Telegram.ChatID, Telegram.SendMsg);

		MsgLength = strlen((char*)TXBuffer);
		sprintf((char*)TXBuffer,  "POST  https://api.telegram.org/bot%s/sendMessage HTTP/1.1\r\n"\
		                        "Host:api.telegram.org\r\n"\
								"Content-Type: application/json\r\n"\
								"Content-Length: %d\r\n\r\n"\
		  					    "{\"chat_id\":\"%ld\",\"text\":\"%s\"}\r\n\r\n\r\n\r\n",Telegram.Token, MsgLength,Telegram.ChatID, Telegram.SendMsg);
		sprintf( (char *) buf, "%s",TXBuffer );
		if(SSL_Send_Data()){
			Flag=SSL_Read_Data();
		}


	}

	return Flag;
}

uint8_t SSL_Read_Data(void){

	uint16_t len;

		  /*
		   * 7. Read the HTTP response
		   */
		   mbedtls_printf( "  < Read from server:" );

		  do
		  {
		    len = sizeof( buf ) - 1;
		    memset( buf, 0, sizeof( buf ) );
		    ret = mbedtls_ssl_read( &ssl, buf, len );

		    if( ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE )
		    {
		      continue;
		    }

		    if( ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY )
		    {
		      break;
		    }

		    if( ret < 0 )
		    {
		      mbedtls_printf( "failed\n  ! mbedtls_ssl_read returned %d\n\n\r\n", ret );
		      break;
		    }

		    if( ret == 0 )
		    {
		      mbedtls_printf( "\n\nEOF\n\n\r\n" );
		      break;
		    }

	    len = ret;
		    mbedtls_printf( " %d bytes read\n\n%s\r\n", len, (char *) buf );
		    break;
		  }
		  while( 1 );

		  return 1;

}

uint8_t SSL_Send_Data(void){

	uint16_t len;

	mbedtls_printf( "  > Write to server:" );

	len = strlen((char *) buf);

	while( ( ret = mbedtls_ssl_write( &ssl, buf, len ) ) <= 0 )
	  {
	    if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
	    {
	      mbedtls_printf( " failed\n  ! mbedtls_ssl_write returned %d\n\n\r\n", ret );
	      return 0;
	   }
	 }

	 len = ret;
	// mbedtls_printf( " %d bytes written\n\n%s\r\n", len, (char *) buf );

	 return 1;

}

uint8_t Connect_Tolegram(void){

	int len;

	  /*
	   * 0. Initialize the RNG and the session data
	   */
	#ifdef MBEDTLS_MEMORY_BUFFER_ALLOC_C
	  mbedtls_memory_buffer_alloc_init(memory_buf, sizeof(memory_buf));
	#endif

	  mbedtls_ssl_init(&ssl);
	  mbedtls_ssl_config_init(&conf);
	  mbedtls_x509_crt_init(&cert);
	  mbedtls_ctr_drbg_init(&ctr_drbg);

	  mbedtls_printf( "\n  . Seeding the random number generator...\r\n" );

	  mbedtls_entropy_init( &entropy );
	  len = strlen((char *)pers);
	  if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
	                             (const unsigned char *) pers, len ) ) != 0 )
	  {
	    mbedtls_printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\r\n", ret );
	    goto exit;
	  }

	  mbedtls_printf( " ok\n" );

	  /*
	   * 0. Initialize certificates
	   */
	  mbedtls_printf( "  . Loading the CA root certificate ...\r\n" );

	  ret = mbedtls_x509_crt_parse( &cert, (const unsigned char *) TELEGRAM_CERTIFICATE_ROOT,
			  mbedtls_telegram_root_certificate_len );
	  if( ret < 0 )
	  {
	    mbedtls_printf( " failed\n  !  mbedtls_x509_crt_parse returned -0x%x\r\n", -ret );
	    goto exit;
	  }

	  mbedtls_printf( " ok (%d skipped)\n", ret );

	  /*
	   * 1. Start the connection
	   */
	  mbedtls_printf( "  . Connecting to tcp/%s/%s...\r\n", SERVER_NAME, SERVER_PORT );

	  if( ( ret = mbedtls_net_connect( &server_fd, SERVER_NAME,
	                                       SERVER_PORT, MBEDTLS_NET_PROTO_TCP ) ) != 0 )
	  {
	    mbedtls_printf( " failed\n  ! mbedtls_net_connect returned %d\r\n", ret );
	    goto exit;
	  }

	  mbedtls_printf( " ok\r\n" );

	  /*
	   * 2. Setup stuff
	   */
	  mbedtls_printf( "  . Setting up the SSL/TLS structure...\r\n" );

	  if( ( ret = mbedtls_ssl_config_defaults( &conf,
	                  MBEDTLS_SSL_IS_CLIENT,
	                  MBEDTLS_SSL_TRANSPORT_STREAM,
	                  MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
	  {
	    mbedtls_printf( " failed\n  ! mbedtls_ssl_config_defaults returned %d\r\n", ret );
	    goto exit;
	  }

	  mbedtls_printf( " ok\n" );

	  /* OPTIONAL is not optimal for security,
	   * but makes interop easier in this simplified example */
	  mbedtls_ssl_conf_authmode( &conf, MBEDTLS_SSL_VERIFY_OPTIONAL );
	  mbedtls_ssl_conf_ca_chain( &conf, &cert, NULL );
	  mbedtls_ssl_conf_rng( &conf, mbedtls_ctr_drbg_random, &ctr_drbg );

	  if( ( ret = mbedtls_ssl_setup( &ssl, &conf ) ) != 0 )
	  {
	    mbedtls_printf( " failed\n  ! mbedtls_ssl_setup returned %d\r\n", ret );
	    goto exit;
	  }

	  if( ( ret = mbedtls_ssl_set_hostname( &ssl, "localhost" ) ) != 0 )
	  {
	    mbedtls_printf( " failed\n  ! mbedtls_ssl_set_hostname returned %d\r\n", ret );
	    goto exit;
	  }

	  mbedtls_ssl_set_bio( &ssl, &server_fd, mbedtls_net_send, mbedtls_net_recv, NULL );

	  /*
	   * 4. Handshake
	   */
	  mbedtls_printf( "  . Performing the SSL/TLS handshake...\r\n" );

	  while( ( ret = mbedtls_ssl_handshake( &ssl ) ) != 0 )
	  {
	    if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
	    {
	      mbedtls_printf( " failed\n  ! mbedtls_ssl_handshake returned -0x%x\r\n", -ret );
	      goto exit;
	    }
	  }

	  mbedtls_printf( " ok\n\r\n" );

	  /*
	   * 5. Verify the server certificate
	   */
	  mbedtls_printf( "  . Verifying peer X.509 certificate...\r\n" );

	  if( ( flags = mbedtls_ssl_get_verify_result( &ssl ) ) != 0 )
	  {

	    mbedtls_printf( " failed\n" );
	    mbedtls_x509_crt_verify_info( (char *)vrfy_buf, sizeof( vrfy_buf ), "  ! ", flags );

	    mbedtls_printf( "%s\n", vrfy_buf );
	  }
	  else
	  {
	    mbedtls_printf( " ok\n\r\n" );
	  }

	  return 1;
	  exit:
	  return 0;


}


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



void DHCP_Task(void const * argument){
	  struct netif *netif = (struct netif *) argument;
	  ip_addr_t ipaddr;
	  ip_addr_t netmask;
	  ip_addr_t gw;
	  struct dhcp *dhcp;



	  for (;;)
	  {
		 // printf("DHCP_Task\r\n");
		  switch (Ethernet.DHCP_State)
	    {
	    case DHCP_START:
	      {
	        ip_addr_set_zero_ip4(&netif->ip_addr);
	        ip_addr_set_zero_ip4(&netif->netmask);
	        ip_addr_set_zero_ip4(&netif->gw);
	        Ethernet.DHCP_State = DHCP_WAIT_ADDRESS;
	        printf ("  State: Looking for DHCP server ...\r\n");
	        dhcp_start(netif);
	      }
	      break;

	    case DHCP_WAIT_ADDRESS:
	      {
	        if (dhcp_supplied_address(netif))
	        {
	        	Ethernet.DHCP_State = DHCP_ADDRESS_ASSIGNED;

	          sprintf((char *)Ethernet.DHCPIPTxt, "%s", ip4addr_ntoa(netif_ip4_addr(netif)));
	          printf ("IP address assigned by a DHCP server: %s\r\n", Ethernet.DHCPIPTxt);
	          Ethernet.DHCPFlag=1;
	        }
	        else
	        {
	          dhcp = (struct dhcp *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

	          /* DHCP timeout */
	          if (dhcp->tries > MAX_DHCP_TRIES)
	          {
	        	  Ethernet.DHCP_State = DHCP_TIMEOUT;

	            /* Static address used */
	            IP_ADDR4(&ipaddr, IP_ADDR0 ,IP_ADDR1 , IP_ADDR2 , IP_ADDR3 );
	            IP_ADDR4(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
	            IP_ADDR4(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
	            netif_set_addr(netif, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gw));


	            sprintf((char *)Ethernet.DHCPIPTxt, "%s", ip4addr_ntoa(netif_ip4_addr(netif)));
	            printf ("DHCP Timeout !! \r\n");
	            printf ("Static IP address: %s\r\n", Ethernet.DHCPIPTxt);
	          }
	        }
	      }
	      break;
	  case DHCP_LINK_DOWN:
	    {
	    	Ethernet.DHCP_State = DHCP_OFF;

	      printf ("The network cable is not connected \r\n");
	    }
	    break;
	    default: break;
	    }

	    /* wait 500 ms */
	    osDelay(500);
	  }

}

uint8_t comparestring(uint8_t *string1, uint8_t *string2,int size){
	  uint16_t i;
	  i = memcmp(string1, string2, size);
	  if(!i)
	  {
	    return 1;
	  }
	  else
	  {
	    return 0;
	  }

}
