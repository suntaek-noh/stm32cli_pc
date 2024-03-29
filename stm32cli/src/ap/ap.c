/*
 * ap.c
 *
 *  Created on: Apr 13, 2022
 *      Author: suntaek.noh
 */

#include "ap.h"
#include "boot/boot.h"



enum
{
  FILE_TYPE_FW,
  FILE_TYPE_BIN,
};

#define TX_BLOCK_LENGTH   512

int32_t getFileSize(char *file_name);

void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600);
}

void apMain(int argc, char *argv[])
{
  bool ret;
  uint8_t err_code;

  uint8_t   uart_ch;
  char      *uart_port;
  uint32_t  uart_baud;
  uint8_t   boot_ver[32];
  uint8_t   boot_name[32];
  uint8_t   firm_ver[32];
  uint8_t   firm_name[32];

  uint32_t  pre_time;
  uint32_t  exe_time;

  uint8_t   file_type;
  uint32_t  file_addr;
  int32_t   file_size;
  char      file_name[256];
  uint8_t   file_run = false;

  FILE      *fp;

  (void)file_type;

  if (argc != 7)
  {
    logPrintf("stm32cli com1 115200 type[fw:bin] 0x8010000 file_name run[0:1]\n");
    apExit();
  }

  uart_ch   = _DEF_UART2;
  uart_port = argv[1];
  uart_baud = (int32_t)strtoul(argv[2], (char **)NULL, (int) 0);

  logPrintf("uart ch   : %d\n", uart_ch);
  logPrintf("uart port : %s\n", uart_port);
  logPrintf("uart baud : %d bps\n", uart_baud);

  if(strcmp(argv[3], "fw") == 0)
  {
    file_type = FILE_TYPE_FW;
    logPrintf("file type : firmware\r\n");

  }
  else if(strcmp(argv[3], "bin") == 0)
  {
    file_type = FILE_TYPE_BIN;
    logPrintf("file type : binary\r\n");

  }
  else
  {
    logPrintf("file type error\r\n");
    apExit();
  }

  file_addr = (uint32_t)strtoul(argv[4], (char **)NULL, (int) 0);
  logPrintf("file addr : 0x%X\n", file_addr);

  strcpy(file_name, argv[5]);
  logPrintf("file name : %s\n", file_name);

  file_size = getFileSize(file_name);
  if(file_size <= 0)
  {
    logPrintf("file size error\n");
    apExit();
  }
  logPrintf("file size : %d bytes\n", file_size);

  if(*argv[6] == '1')
  {
    file_run = true;
    logPrintf("file run : true\n");
  }
  else
  {
    logPrintf("file run : false\n");
  }



  // -- boot 시작
  ret = bootInit(uart_ch, uart_port, uart_baud);
  if(ret != true)
  {
    logPrintf("bootInit Fail\n");
    apExit();
  }

  logPrintf("\nboot start....\n");


  while(1)
  {
    //cliMain();

    err_code = bootCmdReadBootVersion(boot_ver);
    if(err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootVersion fail : %d\r\n", err_code);
      break;
    }

    logPrintf("boot ver \t: %s\n", boot_ver);


    err_code = bootCmdReadBootName(boot_name);
    if(err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootName fail : %d\r\n", err_code);
      break;
    }

    logPrintf("boot name \t: %s\n", boot_name);

    err_code = bootCmdReadFirmVersion(firm_ver);
    if(err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmVersion fail : %d\r\n", err_code);
      break;
    }

    logPrintf("firm ver \t: %s\n", firm_ver);

    err_code = bootCmdReadFirmName(firm_name);
    if(err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmName fail : %d\r\n", err_code);
      break;
    }

    logPrintf("firm name \t: %s\n", firm_name);


    // -- Flash Erase
    //
    logPrintf("flash erase \t: ");
    pre_time = millis();
    err_code = bootCmdFlashErase(file_addr, file_size, 5000);
    exe_time = millis() - pre_time;
    if(err_code != CMD_OK)
    {
      logPrintf("\nbootCmdFlashErase fail : %d\n", err_code);
      break;
    }

    logPrintf("OK (%dms)\n", exe_time);


    // --Flash Write
    //
    if((fp = fopen(file_name, "rb")) == NULL)
    {
      logPrintf("unable to open %s\n", file_name);
      apExit();
    }

    uint32_t addr;
    uint32_t len;
    bool write_done = false;
    uint8_t tx_buf[TX_BLOCK_LENGTH];

    addr = file_addr;   // 플레쉬 시작 주소

    pre_time = millis();
    while(1)
    {
      if(!feof(fp))   // 파일의 끝 확인
      {
        len = fread(tx_buf, 1, TX_BLOCK_LENGTH, fp);

        err_code = bootCmdFlashWrite(addr, tx_buf, len, 1000);
        if(err_code == CMD_OK)
        {
          addr += len;

          logPrintf("flash write \t: %d%%\r", (addr-file_addr)*100 / file_size);

          if((addr-file_addr) >= file_size)  // write 확인
          {
            write_done = true;
            break;
          }
        }
        else
        {
          logPrintf("bootCmdFlashWrite fail : 0x%X, %d\n", addr, err_code);
          break;
        }
      }
      else
      {
        break;
      }

    }

    fclose(fp);

    exe_time = millis() - pre_time;
    logPrintf("\n");

    if(write_done == true)
    {
      logPrintf("flash write \t : OK (%dms)\n", exe_time);
      if(file_run == true)
      {
        err_code = bootCmdJumpToFw();
        if(err_code == CMD_OK)
        {
          logPrintf("jump to fw \t : OK\n");
        }
        else
        {
          logPrintf("jump to fw \t : Fail, %d\n", err_code);
        }
        bootDeInit(uart_ch);
      }
    }
    else
    {
      logPrintf("flash write \t : Fail \n");
    }



    break;


#if 0
    if (uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx_data;

      rx_data = uartRead(_DEF_UART1);

      if (rx_data == '1')
      {
        uint8_t tx_data;

        tx_data = 1;
        if (cmdSendCmdRxResp(&cmd, 0x10, &tx_data, 1, 1000) == true)
        {
          printf("LED ON\n");
        }
        else
        {
          printf("LED ON Fail\n");
        }
      }

      if (rx_data == '2')
      {
        uint8_t tx_data;

        tx_data = 0;
        if (cmdSendCmdRxResp(&cmd, 0x10, &tx_data, 1, 1000) == true)
        {
          printf("LED OFF\n");
        }
        else
        {
          printf("LED OFF Fail\n");
        }
      }

      if (rx_data == '3')
      {
        uint8_t tx_data;

        tx_data = 2;
        if (cmdSendCmdRxResp(&cmd, 0x10, &tx_data, 1, 1000) == true)
        {
          printf("LED Toggle\n");
        }
        else
        {
          printf("LED Toggle Fail\n");
        }
      }
    }
#endif
  }


  apExit();

}

void apExit(void)
{
  for (int i=0; i<UART_MAX_CH; i++)
  {
    uartClose(i);
  }
  printf("\ncli exit\n");
  exit(0);
}

int32_t getFileSize(char *file_name)
{
  int32_t ret = -1;

  FILE *fp;

  if((fp = fopen(file_name, "rb")) == NULL)
  {
    fprintf(stderr, "Unable to open %s\n", file_name);
    return -1;
  }
  else
  {
    fseek(fp, 0, SEEK_END);  // -- 파일의 제일 마지막 주소
    ret = ftell(fp);
    fclose(fp);
  }

  return ret;
}



