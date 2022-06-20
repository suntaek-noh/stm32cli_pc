/*
 * main.c
 *
 *  Created on: Apr 13, 2022
 *      Author: suntaek.noh
 */


#include "main.h"



void exitISR(int sig)
{
  apExit();
}

int main(int argc, char *argv[])
{
  signal(SIGINT, exitISR);    //ctrl + c 눌렀을때 호출 되는 함수
  setbuf(stdout, NULL);       //setbuf는 도스에서 콘솔쪽 출력을 버퍼링 하는데, 그걸 하지 않게 하기 위해
                              // 바로바로 출력 하도록

  hwInit();
  apInit();

  apMain(argc, argv);

  return 0;
}

