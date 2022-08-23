#include "spi.h"
#include "stdint.h"
#include "gpio.h"
/*******************************************************************************
* Function Name		: LIS3DH_ReadReg
* Description		: Generic Reading function. It must be fullfilled with either
*			: I2C or SPI reading functions					
* Input			: Register Address
* Output		: Data REad
* Return		: None
*******************************************************************************/
uint8_t LIS3DH_ReadReg(uint8_t Reg, uint8_t* Data){
    uint8_t tx[2] = { Reg | 0x80, 0xFF }; // Register and dummy data
    uint8_t rx[2];
    HAL_GPIO_WritePin( SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive( &hspi1, tx, rx, 2, 100 );
    HAL_GPIO_WritePin( SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
    *Data= rx[1];
    return 1;
}


/*******************************************************************************
* Function Name		: LIS3DH_WriteReg
* Description		: Generic Writing function. It must be fullfilled with either
*			: I2C or SPI writing function
* Input			: Register Address, Data to be written
* Output		: None
* Return		: None
*******************************************************************************/
uint8_t LIS3DH_WriteReg(uint8_t WriteAddr, uint8_t Data){
    uint8_t tx[2] = { WriteAddr & 0x7F, Data }; // Register and data to write
    HAL_GPIO_WritePin( SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit( &hspi1, tx, 2, 100 );
    HAL_GPIO_WritePin( SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
    return 1;
}