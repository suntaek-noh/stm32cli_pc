/*
 * boot.c
 *
 *  Created on: 2022. 10. 9.
 *      Author: sunta
 */

#include "boot.h"



#define BOOT_CMD_READ_BOOT_VERSION      0x00
#define BOOT_CMD_READ_BOOT_NAME         0x01
#define BOOT_CMD_READ_FIRM_VERSION      0x02
#define BOOT_CMD_READ_FIRM_NAME         0x03
#define BOOT_CMD_FLASH_ERASE            0x04
#define BOOT_CMD_FLASH_WRITE            0x05
#define BOOT_CMD_JUMP_TO_FW             0x08

#define BOOT_CMD_LED_CONTROL            0x10

static cmd_t cmd;


bool bootInit(uint8_t channel, char *port_name, uint32_t baud)
{
  bool ret = true;
  cmdInit(&cmd);

  uartSetPortName(channel, port_name);

  ret = cmdOpen(&cmd, channel, baud);

  return ret;
}

bool bootDeInit(uint8_t channel)
{
  uartClose(channel);
  return true;
}

uint8_t bootCmdReadBootVersion(uint8_t *p_version)
{
  bool ret;
  uint8_t err_code = CMD_OK;

  cmd_t *p_cmd = &cmd;


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_BOOT_VERSION, NULL, 0, 500);     // 커맨드를 보내고 500ms 동안 응답을 기다린다.

  if(ret == true && p_cmd->error == CMD_OK)
  {
    for(int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_version[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}

uint8_t bootCmdReadBootName(uint8_t *p_str)
{
  bool ret;
  uint8_t err_code = CMD_OK;

  cmd_t *p_cmd = &cmd;


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_BOOT_NAME, NULL, 0, 500);     // 커맨드를 보내고 500ms 동안 응답을 기다린다.

  if(ret == true && p_cmd->error == CMD_OK)
  {
    for(int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_str[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}

uint8_t bootCmdReadFirmVersion(uint8_t *p_version)
{
  bool ret;
  uint8_t err_code = CMD_OK;

  cmd_t *p_cmd = &cmd;


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_FIRM_VERSION, NULL, 0, 500);     // 커맨드를 보내고 500ms 동안 응답을 기다린다.

  if(ret == true && p_cmd->error == CMD_OK)
  {
    for(int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_version[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}

uint8_t bootCmdReadFirmName(uint8_t *p_str)
{
  bool ret;
  uint8_t err_code = CMD_OK;

  cmd_t *p_cmd = &cmd;


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_FIRM_NAME, NULL, 0, 500);     // 커맨드를 보내고 500ms 동안 응답을 기다린다.

  if(ret == true && p_cmd->error == CMD_OK)
  {
    for(int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_str[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}

uint8_t bootCmdFlashErase(uint32_t addr, uint32_t length, uint32_t timeout)     // 지울때는 사이즈마다 시간이 다를수 있어서
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;
  uint8_t tx_buf[8];


  tx_buf[0] = (uint8_t)(addr >> 0);
  tx_buf[1] = (uint8_t)(addr >> 8);
  tx_buf[2] = (uint8_t)(addr >> 16);
  tx_buf[3] = (uint8_t)(addr >> 24);

  tx_buf[4] = (uint8_t)(length >> 0);
  tx_buf[5] = (uint8_t)(length >> 8);
  tx_buf[6] = (uint8_t)(length >> 16);
  tx_buf[7] = (uint8_t)(length >> 24);


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_FLASH_ERASE, tx_buf, 8, timeout);     // 커맨드를 보내고 500ms 동안 응답을 기다린다.

  if(ret == true && p_cmd->error == CMD_OK)
  {
    err_code = CMD_OK;
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}

uint8_t bootCmdFlashWrite(uint32_t addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;
  uint8_t *tx_buf;

  if(length > CMD_MAX_DATA_LENGTH)
  {
    err_code = BOOT_ERR_BUF_OVF;
    return err_code;
  }

  tx_buf = p_cmd->tx_packet.data;

  tx_buf[0] = (uint8_t)(addr >> 0);
  tx_buf[1] = (uint8_t)(addr >> 8);
  tx_buf[2] = (uint8_t)(addr >> 16);
  tx_buf[3] = (uint8_t)(addr >> 24);

  tx_buf[4] = (uint8_t)(length >> 0);
  tx_buf[5] = (uint8_t)(length >> 8);
  tx_buf[6] = (uint8_t)(length >> 16);
  tx_buf[7] = (uint8_t)(length >> 24);

  for(int i=0; i<length; i++)
  {
    tx_buf[8+i] = p_data[i];
  }


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_FLASH_WRITE, tx_buf, 8+length, timeout);     // 커맨드를 보내고 500ms 동안 응답을 기다린다.

  if(ret == true && p_cmd->error == CMD_OK)
  {
    err_code = CMD_OK;
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}


uint8_t bootCmdJumpToFw(void)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_JUMP_TO_FW, NULL, 0, 100);     // 커맨드를 보내고 500ms 동안 응답을 기다린다.

  if(ret == true && p_cmd->error == CMD_OK)
  {
    err_code = CMD_OK;
  }
  else
  {
    err_code = p_cmd->error;
  }


  return err_code;
}
