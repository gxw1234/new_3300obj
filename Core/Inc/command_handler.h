#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "main.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// 命令包头结构
typedef struct _CMD_HEADER {
  uint8_t cmd_id;        // 命令ID
  uint8_t spi_index;     // SPI索引
  uint16_t data_len;     // 数据长度
} CMD_HEADER, *PCMD_HEADER;

// 命令ID定义
#define CMD_SPI_INIT        0x01    // SPI初始化命令
#define CMD_SPI_WRITE       0x02    // SPI写数据命令
#define CMD_SPI_READ        0x03    // SPI读数据命令
#define CMD_SPI_TRANSFER    0x04    // SPI读写数据命令

// SPI索引定义
#define SPI1_CS0    0
#define SPI1_CS1    1
#define SPI1_CS2    2
#define SPI2_CS0    3
#define SPI2_CS1    4
#define SPI2_CS2    5

// SPI配置结构体
typedef struct _SPI_CONFIG {
  uint8_t   Mode;            // SPI控制方式:0-硬件控制（全双工模式）,1-硬件控制（半双工模式），2-软件控制（半双工模式）,3-单总线模式，数据线输入输出都为MOSI,4-软件控制（全双工模式）  
  uint8_t   Master;          // 主从选择控制:0-从机，1-主机  
  uint8_t   CPOL;            // 时钟极性控制:0-SCK空闲时为低电平，1-SCK空闲时为高电平  
  uint8_t   CPHA;            // 时钟相位控制:0-第一个SCK时钟采样，1-第二个SCK时钟采样  
  uint8_t   LSBFirst;        // 数据移位方式:0-MSB在前，1-LSB在前  
  uint8_t   SelPolarity;     // 片选信号极性:0-低电平选中，1-高电平选中  
  uint32_t  ClockSpeedHz;    // SPI时钟频率:单位为HZ，硬件模式下最大50000000，最小390625，频率按2的倍数改变  
} SPI_CONFIG, *PSPI_CONFIG;

/**
 * @brief 处理接收到的命令
 * 
 * @param Buf 接收到的数据缓冲区
 * @param Len 数据长度
 * @return int8_t 处理结果，0表示成功
 */
int8_t Process_Command(uint8_t* Buf, uint32_t *Len);

#endif /* COMMAND_HANDLER_H */
