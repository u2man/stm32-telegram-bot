/*
 * global.h
 *
 *  Created on: Jul 23, 2022
 *      Author: Usman
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_


#include "main.h"
#include "cmsis_os.h"
#include "crc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "lwip.h"
#include "quadspi.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"
#include "app_touchgfx.h"

#include <stm32746g_discovery_qspi.h>
#include <ft5336.h>
#include "stm32746g_discovery.h"

#include <stdio.h>
#include <string.h>
#include <telegram.h>


#include "lwipopts.h"
#include "lwip/dhcp.h"
#include "lwip/apps/sntp.h"
//#include "app_ethernet.h"
#include "ethernetif.h"
#include "lwip/netif.h"
#include "dns.h"
//#include "tcp_client.h"
#include "lwip/tcp.h"
#include "lwip/api.h"
#include "lwip.h"
#include "mbedtls.h"
#include "mbedtls/platform.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"
#include "mbedtls/memory_buffer_alloc.h"



extern osThreadId DHCPTaskHandle;

#endif /* INC_GLOBAL_H_ */
