#include "command_handler.h"
#include "main.h"

// 外部变量声明
extern UART_HandleTypeDef huart1;

/**
 * @brief 处理SPI初始化命令
 * 
 * @param spi_index SPI索引
 * @param pConfig SPI配置结构体指针
 */
static void Process_SPI_Init(uint8_t spi_index, PSPI_CONFIG pConfig) {
    // 在此处显示接收到的SPI配置信息
    char buffer[128];
    sprintf(buffer, "SPI Init: Index=%d, Mode=%d, Master=%d, CPOL=%d, CPHA=%d, LSB=%d, SelPol=%d, Clock=%lu\r\n", 
            spi_index, pConfig->Mode, pConfig->Master, pConfig->CPOL, pConfig->CPHA, 
            pConfig->LSBFirst, pConfig->SelPolarity, pConfig->ClockSpeedHz);
    
    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);
    
    // TODO: 这里将来实现真正的SPI初始化
}

/**
 * @brief 处理接收到的命令
 * 
 * @param Buf 接收到的数据缓冲区
 * @param Len 数据长度
 * @return int8_t 处理结果，0表示成功
 */
int8_t Process_Command(uint8_t* Buf, uint32_t *Len) {
    // 先判断数据长度是否足够包含命令头
    if (*Len >= sizeof(CMD_HEADER)) {
        // 解析命令头
        CMD_HEADER* header = (CMD_HEADER*)Buf;
        
        // 根据命令ID处理不同类型的命令
        switch (header->cmd_id) {
            case CMD_SPI_INIT:
                if (*Len >= sizeof(CMD_HEADER) + sizeof(SPI_CONFIG)) {
                    // 提取SPI配置数据
                    SPI_CONFIG* spi_config = (SPI_CONFIG*)(Buf + sizeof(CMD_HEADER));
                    
                    // 处理SPI初始化命令
                    Process_SPI_Init(header->spi_index, spi_config);
                } else {
                    // 数据长度不足，发送错误信息
                    char* error_msg = "Error: Insufficient data for SPI_INIT command\r\n";
                    HAL_UART_Transmit(&huart1, (uint8_t*)error_msg, strlen(error_msg), 100);
                }
                break;
                
            // 其他命令处理...
            case CMD_SPI_WRITE:
            case CMD_SPI_READ:
            case CMD_SPI_TRANSFER:
                // TODO: 实现其他SPI命令的处理
                {
                    char* msg = "Received other SPI command (not implemented yet)\r\n";
                    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
                }
                break;
                
            default:
                // 非命令数据，仅打印接收到的原始数据
                HAL_UART_Transmit(&huart1, Buf, *Len, 100);
                break;
        }
    } else {
        // 数据过短，直接打印原始数据
        HAL_UART_Transmit(&huart1, Buf, *Len, 100);
    }
    
    return 0;
}
