/*
 * imu.h
 *
 *  Created on: 31 mag 2023
 *      Author: David
 */

#ifndef SENSORS_IMU_H_
#define SENSORS_IMU_H_

#include "main.h"

#define LSM6DSOX_ID		0x6c

extern stmdev_ctx_t LSM6DSOX_ctx;
extern stmdev_ctx_t LIS2MDL_ctx;

enum IMU_StatusTypeDef{
	IMU_OK,
	IMU_ERROR,
	IMU_BUSY,
	IMU_WRONG_ID
};


void IMU_init(void);

#endif /* SENSORS_IMU_H_ */
