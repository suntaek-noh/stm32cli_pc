/*
 * st7567.h
 *
 *  Created on: 2022. 4. 29.
 *      Author: suntaek.noh
 */

#ifndef SRC_COMMON_HW_INCLUDE_LCD_ST7567_H_
#define SRC_COMMON_HW_INCLUDE_LCD_ST7567_H_

#include "hw_def.h"


#ifdef _USE_HW_ST7567

#include "lcd.h"


bool st7567Init(lcd_driver_t *p_driver);


#endif

#endif /* SRC_COMMON_HW_INCLUDE_LCD_ST7567_H_ */
