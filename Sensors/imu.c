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

IMU_StatusTypeDef  LSM6DSOX_init(void);

stmdev_ctx_t LSM6DSOX_ctx;
stmdev_ctx_t LIS2MDL_ctx;

//Write to a generic SPI register
static int32_t LMS6DSOX_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len){
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(handle, &reg, 1, 1000);
	HAL_SPI_Transmit(handle, (uint8_t *)bufp, len, 1000);
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);
	return 0;
}

//Read from a generic SPI register
static int32_t LMS6DSOX_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len){
	reg |= 0x80;
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(handle, &reg, 1, 1000);
	HAL_SPI_Receive(handle, bufp, len, 1000);
	HAL_GPIO_WritePin(CS_LSM6DSOX_GPIO_Port, CS_LSM6DSOX_Pin, GPIO_PIN_SET);
	return 0;
}

// Read from a generic SPI register of LIS2MDL magnetometer
static int32_t LIS2MDL_read(void *handle, uint8_t reg, uint8_t *bufp,
        					uint16_t len){
	reg |= 0x80;
	HAL_GPIO_WritePin(CS_LIS2MDL_GPIO_Port, CS_LIS2MDL_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(handle, &reg, 1, 1000);
	HAL_SPI_Receive(handle, bufp, len, 1000);
	HAL_GPIO_WritePin(CS_LIS2MDL_GPIO_Port, CS_LIS2MDL_Pin, GPIO_PIN_SET);
	return 0;
}

static int32_t LIS2MDL_write(){
	HAL_GPIO_WritePin(CS_LIS2MDL_GPIO_Port, CS_LIS2MDL_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(handle, &reg, 1, 1000);
	HAL_SPI_Transmit(handle, (uint8_t *)bufp, len, 1000);
	HAL_GPIO_WritePin(CS_LIS2MDL_GPIO_Port, CS_LIS2MDL_Pin, GPIO_PIN_SET);
}

IMU_StatusTypeDef  LSM6DSOX_init(){
	uint8_t whoami = 0;
	uint8_t rst = 0;
	LSM6DSOX_ctx.write_reg = &LMS6DSOX_write;
	LSM6DSOX_ctx.read_reg = &LMS6DSOX_read;
	LSM6DSOX_ctx.handle = &hspi1;

	// Check device id
	lsm6dsox_device_id_get(&LSM6DSOX_ctx, &whoami);

	if(whoami != LSM6DSOX_ID)
		return IMU_WRONG_ID;

	// Restore default configuration
	lsm6dsox_reset_set(&LSM6DSOX_ctx, PROPERTY_ENABLE);
	do{
		lsm6dsox_reset_get(&LSM6DSOX_ctx, &rst);
	}while(rst);
	// Disable i3c
	lsm6dsox_i3c_disable_set(&LSM6DSOX_ctx, LSM6DSOX_I3C_DISABLE);
	// Enable Block Data Update
	lsm6dsox_block_data_update_set(&LSM6DSOX_ctx, PROPERTY_ENABLE);
	// Set Output Data Rate
	lsm6dsox_xl_data_rate_set(&LSM6DSOX_ctx, LSM6DSOX_XL_ODR_104Hz);
	lsm6dsox_gy_data_rate_set(&LSM6DSOX_ctx, LSM6DSOX_GY_ODR_104Hz);
	//Set full scale
	lsm6dsox_xl_full_scale_set(&LSM6DSOX_ctx, LSM6DSOX_2g);
	lsm6dsox_gy_full_scale_set(&LSM6DSOX_ctx, LSM6DSOX_2000dps);
}

void IMU_init(){

	IMU_StatusTypeDef retval = LSM6DSOX_init();
	if(retval != IMU_OK)
		return;



	LIS2MDL_ctx.write_reg = &LIS2MDL_write;
	LIS2MDL_ctx.read_reg = &LIS2MDL_read;
	LIS2MDL_ctx.handle = &hspi3;




}

void



