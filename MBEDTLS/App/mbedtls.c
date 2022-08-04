/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : mbedtls.c
  * Description        : This file provides code for the configuration
  *                      of the mbedtls instances.
  ******************************************************************************
  ******************************************************************************
   * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "mbedtls.h"

/* USER CODE BEGIN 0 */
#include "global.h"
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* Global variables ---------------------------------------------------------*/
mbedtls_ssl_context ssl;
mbedtls_ssl_config conf;
mbedtls_x509_crt cert;
mbedtls_ctr_drbg_context ctr_drbg;
mbedtls_entropy_context entropy;

/* USER CODE BEGIN 2 */






/* USER CODE END 2 */

/* MBEDTLS init function */
void MX_MBEDTLS_Init(void)
{
   /**
  */
  mbedtls_ssl_init(&ssl);
  mbedtls_ssl_config_init(&conf);
  mbedtls_x509_crt_init(&cert);
  mbedtls_ctr_drbg_init(&ctr_drbg);
  mbedtls_entropy_init( &entropy );
  /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */

}

/* USER CODE BEGIN 4 */

void SSL_Client(void){

//	int len,MsgLength;
//
//	  /*
//	   * 0. Initialize the RNG and the session data
//	   */
//	#ifdef MBEDTLS_MEMORY_BUFFER_ALLOC_C
//	  mbedtls_memory_buffer_alloc_init(memory_buf, sizeof(memory_buf));
//	#endif
//
//	  mbedtls_ssl_init(&ssl);
//	  mbedtls_ssl_config_init(&conf);
//	  mbedtls_x509_crt_init(&cert);
//	  mbedtls_ctr_drbg_init(&ctr_drbg);
//
//	  mbedtls_printf( "\n  . Seeding the random number generator...\r\n" );
//
//	  mbedtls_entropy_init( &entropy );
//	  len = strlen((char *)pers);
//	  if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
//	                             (const unsigned char *) pers, len ) ) != 0 )
//	  {
//	    mbedtls_printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\r\n", ret );
//	    goto exit;
//	  }
//
//	  mbedtls_printf( " ok\n" );
//
//	  /*
//	   * 0. Initialize certificates
//	   */
//	  mbedtls_printf( "  . Loading the CA root certificate ...\r\n" );
//
//	  ret = mbedtls_x509_crt_parse( &cert, (const unsigned char *) TELEGRAM_CERTIFICATE_ROOT,
//			  mbedtls_telegram_root_certificate_len );
//	  if( ret < 0 )
//	  {
//	    mbedtls_printf( " failed\n  !  mbedtls_x509_crt_parse returned -0x%x\r\n", -ret );
//	    goto exit;
//	  }
//
//	  mbedtls_printf( " ok (%d skipped)\n", ret );
//
//	  /*
//	   * 1. Start the connection
//	   */
//	  mbedtls_printf( "  . Connecting to tcp/%s/%s...\r\n", SERVER_NAME, SERVER_PORT );
//
//	  if( ( ret = mbedtls_net_connect( &server_fd, SERVER_NAME,
//	                                       SERVER_PORT, MBEDTLS_NET_PROTO_TCP ) ) != 0 )
//	  {
//	    mbedtls_printf( " failed\n  ! mbedtls_net_connect returned %d\r\n", ret );
//	    goto exit;
//	  }
//
//	  mbedtls_printf( " ok\r\n" );
//
//	  /*
//	   * 2. Setup stuff
//	   */
//	  mbedtls_printf( "  . Setting up the SSL/TLS structure...\r\n" );
//
//	  if( ( ret = mbedtls_ssl_config_defaults( &conf,
//	                  MBEDTLS_SSL_IS_CLIENT,
//	                  MBEDTLS_SSL_TRANSPORT_STREAM,
//	                  MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
//	  {
//	    mbedtls_printf( " failed\n  ! mbedtls_ssl_config_defaults returned %d\r\n", ret );
//	    goto exit;
//	  }
//
//	  mbedtls_printf( " ok\n" );
//
//	  /* OPTIONAL is not optimal for security,
//	   * but makes interop easier in this simplified example */
//	  mbedtls_ssl_conf_authmode( &conf, MBEDTLS_SSL_VERIFY_OPTIONAL );
//	  mbedtls_ssl_conf_ca_chain( &conf, &cert, NULL );
//	  mbedtls_ssl_conf_rng( &conf, mbedtls_ctr_drbg_random, &ctr_drbg );
//
//	  if( ( ret = mbedtls_ssl_setup( &ssl, &conf ) ) != 0 )
//	  {
//	    mbedtls_printf( " failed\n  ! mbedtls_ssl_setup returned %d\r\n", ret );
//	    goto exit;
//	  }
//
//	  if( ( ret = mbedtls_ssl_set_hostname( &ssl, "localhost" ) ) != 0 )
//	  {
//	    mbedtls_printf( " failed\n  ! mbedtls_ssl_set_hostname returned %d\r\n", ret );
//	    goto exit;
//	  }
//
//	  mbedtls_ssl_set_bio( &ssl, &server_fd, mbedtls_net_send, mbedtls_net_recv, NULL );
//
//	  /*
//	   * 4. Handshake
//	   */
//	  mbedtls_printf( "  . Performing the SSL/TLS handshake...\r\n" );
//
//	  while( ( ret = mbedtls_ssl_handshake( &ssl ) ) != 0 )
//	  {
//	    if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
//	    {
//	      mbedtls_printf( " failed\n  ! mbedtls_ssl_handshake returned -0x%x\r\n", -ret );
//	      goto exit;
//	    }
//	  }
//
//	  mbedtls_printf( " ok\n\r\n" );
//
//	  /*
//	   * 5. Verify the server certificate
//	   */
//	  mbedtls_printf( "  . Verifying peer X.509 certificate...\r\n" );
//
//	  if( ( flags = mbedtls_ssl_get_verify_result( &ssl ) ) != 0 )
//	  {
//
//	    mbedtls_printf( " failed\n" );
//	    mbedtls_x509_crt_verify_info( (char *)vrfy_buf, sizeof( vrfy_buf ), "  ! ", flags );
//
//	    mbedtls_printf( "%s\n", vrfy_buf );
//	  }
//	  else
//	  {
//	    mbedtls_printf( " ok\n\r\n" );
//	  }
//
//	  /*
//	   * 6. Write the GET request
//	   */
//
//
//
//
//			//sprintf((char*)Modem.TelegramToken,"5280472774:AAFM0KE-gTcRs-JpPPIiq9VoZ4uN2A4CO2g");
//			//Modem.TelegramChatID=903296275;//-705301667;
//		    sprintf((char*)TXBuffer,	"{\"chat_id\":\"%ld\",\"text\":\"%s\"}\r\n\r\n\r\n\r\n",Telegram.ChatID, Telegram.SendMsg);
//
//			MsgLength = strlen((char*)TXBuffer);
//			sprintf((char*)TXBuffer,  "POST  https://api.telegram.org/bot%s/sendMessage HTTP/1.1\r\n"\
//					                        "Host:api.telegram.org\r\n"\
//											"Content-Type: application/json\r\n"\
//											"Content-Length: %d\r\n\r\n"\
//											"{\"chat_id\":\"%ld\",\"text\":\"%s\"}\r\n\r\n\r\n\r\n",Telegram.Token, MsgLength,Telegram.ChatID, Telegram.SendMsg);
//
//
//		  sprintf( (char *) buf, "%s",TXBuffer );
//
//
//	  mbedtls_printf( "  > Write to server:" );
//
//	  //sprintf( (char *) buf, GET_REQUEST );
//	  len = strlen((char *) buf);
//
//	  while( ( ret = mbedtls_ssl_write( &ssl, buf, len ) ) <= 0 )
//	  {
//	    if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
//	    {
//	      mbedtls_printf( " failed\n  ! mbedtls_ssl_write returned %d\n\n\r\n", ret );
//	      goto exit;
//	    }
//	  }
//
//	  len = ret;
//	  mbedtls_printf( " %d bytes written\n\n%s\r\n", len, (char *) buf );
//
//	  /*
//	   * 7. Read the HTTP response
//	   */
//	   mbedtls_printf( "  < Read from server:" );
//
//	  do
//	  {
//	    len = sizeof( buf ) - 1;
//	    memset( buf, 0, sizeof( buf ) );
//	    ret = mbedtls_ssl_read( &ssl, buf, len );
//
//	    if( ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE )
//	    {
//	      continue;
//	    }
//
//	    if( ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY )
//	    {
//	      break;
//	    }
//
//	    if( ret < 0 )
//	    {
//	      mbedtls_printf( "failed\n  ! mbedtls_ssl_read returned %d\n\n\r\n", ret );
//	      break;
//	    }
//
//	    if( ret == 0 )
//	    {
//	      mbedtls_printf( "\n\nEOF\n\n\r\n" );
//	      break;
//	    }
//
//	    len = ret;
//	    mbedtls_printf( " %d bytes read\n\n%s\r\n", len, (char *) buf );
//	    break;
//	  }
//	  while( 1 );
//
//	  mbedtls_ssl_close_notify( &ssl );
//
//	exit:
//	  mbedtls_net_free( &server_fd );
//
//	  mbedtls_x509_crt_free( &cert );
//	  mbedtls_ssl_free( &ssl );
//	  mbedtls_ssl_config_free( &conf );
//	  mbedtls_ctr_drbg_free( &ctr_drbg );
//	  mbedtls_entropy_free( &entropy );
//
//	  if ((ret < 0) && (ret != MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY))
//	  {
//	    Error_Handler();
//	  }
//	  else
//	  {
//	    //Success_Handler();
//	  }

}


/* USER CODE END 4 */

/**
  * @}
  */

/**
  * @}
  */

