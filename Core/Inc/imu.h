/*
 * imu.h
 *
 *  Created on: 31 mag 2023
 *      Author: David
 */

#ifndef SENSORS_IMU_H_
#define SENSORS_IMU_H_

#include "main.h"

extern stmdev_ctx_t LSM6DSOX_ctx;

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
void lsm6dsox_struct_init(void);

#endif /* SENSORS_IMU_H_ */
