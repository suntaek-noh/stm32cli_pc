/*
 * bsp.h
 *
 *  Created on: Apr 13, 2022
 *      Author: suntaek.noh
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"


#define _USE_LOG_PRINTF   1

#if _USE_LOG_PRINTF
#define logPrintf(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define logPrintf(fmt, ...)
#endif


void bspInit(void);
void delay(uint32_t ms);
uint32_t millis(void);



#endif /* SRC_BSP_BSP_H_ */
