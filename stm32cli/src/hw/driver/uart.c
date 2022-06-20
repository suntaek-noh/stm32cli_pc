/*
 * uart.c
 *
 *  Created on: Jan 29, 2022
 *      Author: suntaek.noh
 */


#include "uart.h"
#include "cdc.h"
#include "qbuffer.h"

#ifdef _USE_HW_UART

static bool is_open[UART_MAX_CH];

bool uartInit(void)
{
  for(int i=0; i<UART_MAX_CH; i++)
  {
    is_open[i] = false;
  }

  return true;
}

bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = false;

  switch(ch)
  {
    case _DEF_UART1:
      is_open[ch] = true;
      ret = true;
      break;

    case _DEF_UART2:
      break;

    case _DEF_UART3:
      break;
  }

  return ret;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      if(kbhit())
      {
        ret = 1;
      }
      break;

    case _DEF_UART2:
      break;

    case _DEF_UART3:
      break;
  }

  return ret;
}

uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      ret = getch();
      break;

    case _DEF_UART2:
      break;

    case _DEF_UART3:
      break;
  }

  return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      for(int i=0; i<length; i++)
      {
        putc(p_data[i], stdout);
        ret = length;
      }
      break;

    case _DEF_UART2:
      break;

    case _DEF_UART3:
      break;
  }

  return ret;
}

uint32_t  uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args);

  ret = uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);

  return ret;
}

uint32_t  uartGetBaud(uint8_t ch)
{
  uint32_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      break;

    case _DEF_UART2:
      break;

    case _DEF_UART3:
      break;
  }

  return ret;
}

#endif
