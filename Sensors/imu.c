/*
 * imu.c
 *
 *  Created on: May 28, 2023
 *      Author: David
 */

#include "imu.h"
#include "main.h"
#include "spi.h"
#include "lsm6dsox_reg.h"

stmdev_ctx_t LSM6DSOX_ctx;

//Write to a generic SPI register
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len){
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(handle, &reg, 1, 1000);
	HAL_SPI_Transmit(handle, (uint8_t *)bufp, len, 1000);
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);
	return 0;
}

//Read from a generic SPI register
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len){
	reg |= 0x80;
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(handle, &reg, 1, 1000);
	HAL_SPI_Receive(handle, bufp, len, 1000);
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);
	return 0;
}

void lsm6dsox_struct_init(){
	LSM6DSOX_ctx.write_reg = &platform_write;
	LSM6DSOX_ctx.read_reg = &platform_read;
	LSM6DSOX_ctx.handle = &hspi1;
}


