/*
 * def.h
 *
 *  Created on: Apr 13, 2022
 *      Author: suntaek.noh
 */

#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include <conio.h>
#include <signal.h>

#if defined (__WIN32__) || (__WIN64__)
#include <Windows.h>
#endif



#define _DEF_UART1            0
#define _DEF_UART2            1
#define _DEF_UART3            2
#define _DEF_UART4            3


#define _DEF_LED1             0
#define _DEF_LED2             1
#define _DEF_LED3             2
#define _DEF_LED4             3
#define _DEF_LED5             4
#define _DEF_LED6             5
#define _DEF_LED7             6
#define _DEF_LED8             7

#define _DEF_BUTTON1          0
#define _DEF_BUTTON2          1
#define _DEF_BUTTON3          2
#define _DEF_BUTTON4          3

#define _DEF_SPI1             0
#define _DEF_SPI2             1
#define _DEF_SPI3             2
#define _DEF_SPI4             3

#define _DEF_I2C1             0
#define _DEF_I2C2             1
#define _DEF_I2C3             2
#define _DEF_I2C4             3

#define _DEF_PWM1             0
#define _DEF_PWM2             1
#define _DEF_PWM3             2
#define _DEF_PWM4             3


#define _DEF_INPUT            0
#define _DEF_INPUT_PULLUP     1
#define _DEF_INPUT_PULLDOWN   2
#define _DEF_OUTPUT           3
#define _DEF_OUTPUT_PULLUP    4
#define _DEF_OUTPUT_PULLDOWN  5

#define _DEF_LOW              0
#define _DEF_HIGH             1



#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#if 1
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif


#ifndef map
#define map(value, in_min, in_max, out_min, out_max) ((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#endif
#else

#ifndef CMAX
#define CMAX(a,b) (((a) > (b)) ? (a) : (b))
#define CMIN(a,b) (((a) < (b)) ? (a) : (b))
#endif


#ifndef CMAP
#define CMAP(value, in_min, in_max, out_min, out_max) ((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#endif

#endif

typedef struct
{
  uint8_t version[32];
  uint8_t name[32];
} firm_version_t;


#endif /* SRC_COMMON_DEF_H_ */
