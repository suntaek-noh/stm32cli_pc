/*
 * gd25q128e.h
 *
 *  Created on: 2021. 8. 12.
 *      Author: suntaek.noh
 */

#ifndef SRC_COMMON_HW_INCLUDE_QSPI_GD25Q128E_H_
#define SRC_COMMON_HW_INCLUDE_QSPI_GD25Q128E_H_

/**
  * @brief  GD25Q256E Configuration
  */
#define GD25Q128E_FLASH_SIZE                  (0x1000000)    /* 128 MBits => 16MBytes */
#define GD25Q128E_SECTOR_SIZE                 0x10000        /* 256 sectors of 64KBytes */
#define GD25Q128E_SUBSECTOR_SIZE              0x1000         /* 4096 subsectors of 4kBytes */
#define GD25Q128E_PAGE_SIZE                   0x100          /* 65536 pages of 256 bytes */

#define GD25Q128E_DUMMY_CYCLES_READ           8
#define GD25Q128E_DUMMY_CYCLES_READ_QUAD      4

#define GD25Q128E_BULK_ERASE_MAX_TIME         250000
#define GD25Q128E_SECTOR_ERASE_MAX_TIME       3000
#define GD25Q128E_SUBSECTOR_ERASE_MAX_TIME    800

/**
  * @brief  GD25Q256E Commands
  */
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

/* Identification Operations */
#define READ_ID_CMD                          0x9F
#define READ_ID_CMD2                         0x9F
#define MULTIPLE_IO_READ_ID_CMD              0xAF
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A

/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define WRITE_STATUS_REG_CMD                 0x01

#define READ_STATUS_REG2_CMD                 0x35
#define WRITE_STATUS_REG2_CMD                0x31

#define READ_STATUS_REG3_CMD                 0x15
#define WRITE_STATUS_REG3_CMD                0x11


#define READ_LOCK_REG_CMD                    0xE8
#define WRITE_LOCK_REG_CMD                   0xE5

#define READ_FLAG_STATUS_REG_CMD             0x70
#define CLEAR_FLAG_STATUS_REG_CMD            0x50

#define READ_NONVOL_CFG_REG_CMD              0xB5
#define WRITE_NONVOL_CFG_REG_CMD             0xB1

#define READ_VOL_CFG_REG_CMD                 0x85
#define WRITE_VOL_CFG_REG_CMD                0x81

#define READ_ENHANCED_VOL_CFG_REG_CMD        0x65
#define WRITE_ENHANCED_VOL_CFG_REG_CMD       0x61

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define DUAL_IN_FAST_PROG_CMD                0xA2
#define EXT_DUAL_IN_FAST_PROG_CMD            0xD2
#define QUAD_IN_FAST_PROG_CMD                0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x12

/* Erase Operations */
#define SUBSECTOR_ERASE_CMD                  0x20
#define SECTOR_ERASE_CMD                     0xD8
#define BULK_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

/* One-Time Programmable Operations */
#define READ_OTP_ARRAY_CMD                   0x4B
#define PROG_OTP_ARRAY_CMD                   0x42

#define WRITE            0x02     /* write to memory instruction */
#define QUADWRITE        0x32     /* quad write to memory instruction */
#define WRSR             0x01     /* write status register instruction */
#define WREN             0x06     /* write enable instruction */

#define READ             0x03     /* read from memory instruction */
#define QUADREAD         0x6B     /* read from memory instruction */
#define RDSR             0x05     /* read status register instruction */
#define RDID             0x9F     /* read identification */

#define SE               0x20     /* sector erase instruction */
#define BE               0xC7     /* bulk erase instruction */

#define WIP_FLAG         0x01     /* write in progress(wip) flag */

#define DUMMY_BYTE       0xA5

/* Status Register */
#define GD25Q128E_SR_WIP                      ((uint8_t)0x01)    /*!< Write in progress */
#define GD25Q128E_SR_WREN                     ((uint8_t)0x02)    /*!< Write enable latch */
#define GD25Q128E_SR_BLOCKPR                  ((uint8_t)0x5C)    /*!< Block protected against program and erase operations */
#define GD25Q128E_SR_PRBOTTOM                 ((uint8_t)0x20)    /*!< Protected memory area defined by BLOCKPR starts from top or bottom */
#define GD25Q128E_SR_SRWREN                   ((uint8_t)0x80)    /*!< Status register write enable/disable */





#endif /* SRC_COMMON_HW_INCLUDE_QSPI_GD25Q128E_H_ */


