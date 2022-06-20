/*
 * hw_def.h
 *
 *  Created on: Apr 13, 2022
 *      Author: suntaek.noh
 *  hw 폴더 밑에 있는 모듈에서 공통으로 상요 할수 있게 하는
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"


#define _USE_HW_UART
#define      HW_UART_MAX_CH         3

#define _USE_HW_CLI
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    64

#endif /* SRC_HW_HW_DEF_H_ */
