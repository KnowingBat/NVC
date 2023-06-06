/*
 * imu.c
 *
 *  Created on: May 28, 2023
 *      Author: David
 */

#include "imu.h"
#include "main.h"
#include "spi.h"

// Initialization of accelerometer LIS2DW12
HAL_StatusTypeDef LIS2DW12_Init(void){


	return HAL_OK;
}

HAL_StatusTypeDef LMS6DSO_WriteReg(uint8_t address, uint8_t *pTxData, uint16_t dataSize, uint32_t timeout){
	/* Activate chip select */
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef retVal = HAL_SPI_Transmit(&hspi1, pTxData, dataSize, timeout);
	/* Reset chip select */
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);
	return retVal;
}

HAL_StatusTypeDef LMS6DSO_ReadReg(uint8_t reg, uint8_t pRxData, uint16_t dataSize, uint32_t timeout){
	/* Activate chip select */
	reg = reg | 0x80; // Read command
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef retVal = HAL_SPI_Transmit(&hspi1, (uint8_t *)&reg, dataSize, timeout);
	if(retVal != HAL_OK)
		return retVal;
	HAL_Delay(10);
	retVal = HAL_SPI_Receive(&hspi1, (uint8_t *)&pRxData, dataSize, timeout);
	/* Reset chip select */
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);
	return retVal;
}

// Initialization of 3D ACC+GYRO LSM6DSO
void LMS6DSO_Init(struct LSM6DSO lsm6){
	// Start-up the accelerometer and gyro in the specified mode
	uint8_t pTxData = 0x10;
	// Set to normal mode
	LMS6DSO_WriteReg(CTRL6_C, (uint8_t *)&pTxData, 1, 100);
	// Set to normal operating mode and full scale
	pTxData = lsm6.acc.operatingMode | lsm6.acc.fullScale;
	LMS6DSO_WriteReg(CTRL1_XL, (uint8_t *)&pTxData, 1, 100);
	// Set to normal mode
	pTxData = 0x80;
	LMS6DSO_WriteReg(CTRL7_G, (uint8_t *)&pTxData, 1, 100);
	pTxData = lsm6.gyro.operatingMode | lsm6.gyro.fullScale;
	LMS6DSO_WriteReg(CTRL2_G, (uint8_t *)&pTxData, 1, 100);
	return;
}



