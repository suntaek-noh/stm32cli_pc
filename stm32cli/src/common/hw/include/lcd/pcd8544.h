/*
 * pcd8544.h
 *
 *  Created on: 2022. 3. 14.
 *      Author: suntaek.noh
 */

#ifndef SRC_COMMON_HW_INCLUDE_LCD_PCD8544_H_
#define SRC_COMMON_HW_INCLUDE_LCD_PCD8544_H_

#include "hw_def.h"

#ifdef _USE_HW_PCD8544

#include "lcd.h"


bool pcd8544Init(void);
bool pcd8544InitDriver(lcd_driver_t *p_driver);
//bool pcd8544DrawAvailable(void);
//bool pcd8544RequestDraw(void);
void pcd8544SetWindow(int32_t x, int32_t y, int32_t w, int32_t h);

//uint32_t pcd8544GetFps(void);
//uint32_t pcd8544GetFpsTime(void);

uint16_t pcd8544GetWidth(void);
uint16_t pcd8544GetHeight(void);

bool pcd8544SetCallBack(void (*p_func)(void));
bool pcd8544SendBuffer(uint8_t *p_data, uint32_t length, uint32_t timeout_ms);
//bool pcd8544DrawBuffer(int16_t x, int16_t y, uint16_t *buffer, uint16_t w, uint16_t h);
//bool pcd8544DrawBufferedLine(int16_t x, int16_t y, uint16_t *buffer, uint16_t w);


#endif


#endif /* SRC_COMMON_HW_INCLUDE_LCD_PCD8544_H_ */
