/*
 * ap.c
 *
 *  Created on: Apr 13, 2022
 *      Author: suntaek.noh
 */

#include "ap.h"


void cliTest(cli_args_t *args);


void apInit(void)
{
  logPrintf("stm32cli V1.0\r\n");
  cliOpen(_DEF_UART1, 115200);

  cliAdd("test", cliTest);
}

void apMain(int argc, char *argv[])
{
  uint32_t pre_time;


  pre_time = millis();
  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();
    }

    cliMain();
  }
}

void apExit(void)
{
  printf("cli exit\n");
  exit(0);
}

void cliTest(cli_args_t *args)
{
  bool ret = false;

  if(args->argc == 1 && args->isStr(0,"cnt") == true)
  {
    uint32_t cnt = 0;

    while(cliKeepLoop())
    {
      cliPrintf("cnt = %d\n", cnt++);
      delay(500);
    }

    ret = true;
  }


  if(ret != true)
  {
    cliPrintf("test cnt\n");
  }

}


