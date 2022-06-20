/*
 * hw.c
 *
 *  Created on: Apr 13, 2022
 *      Author: suntaek.noh
 */


#include "hw.h"


void hwInit(void)
{
  bspInit();
  cliInit();

  uartInit();
}
