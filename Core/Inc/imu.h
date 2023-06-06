/*
 * imu.h
 *
 *  Created on: 31 mag 2023
 *      Author: David
 */

#ifndef SENSORS_IMU_H_
#define SENSORS_IMU_H_

#define WHO_AM_I 		0x0F
#define CTRL1_XL		0x10 //Accelerometer control register 1
#define CTRL2_G			0x11 //Gyroscope control register 2
#define CTRL6_C			0x15 //Acc-Power control register
#define CTRL7_G			0x16 //Gyro-Power control register
#define OUT_TEMP_L		0x20 //Temperature register LOW
#define OUT_TEMP_H		0x21 //Temperature register HIGH

enum LSM6DS0_OpMode{
	POWER_DOWN = 0x00,
	LOW_POWER_1_6 = 0xB0,
	LOW_POWER_12_5 = 0x10,
	LOW_POWER_26 = 0x20,
	LOW_POWER_52 = 0x30,
	NORMAL_104 = 0x40,
	NORMAL_208 = 0x50,
	HIGH_PERF_416 = 0x60,
	HIGH_PERF_833 = 0x70,
	HIGH_PERF_1660 = 0x80,
	HIGH_PERF_3330 = 0x90,
	HIGH_PERF_6660 = 0xA0
};

enum LSM6DSO_ACC_FS{
	FS_XL_2 = 0,
	FS_XL_4 = 2,
	FS_XL_8 = 3,
	FS_XL_16 = 1
};

enum LSM6DSO_GYRO_FS{
	FS_G_250 = 0,
	FS_G_500 = 1,
	FS_G_1000 = 2,
	FS_G_2000 = 3
};

struct Acc{
	enum LSM6DS0_OpMode operatingMode;
	enum LSM6DSO_ACC_FS fullScale;
};

struct Gyro{
	enum LSM6DS0_OpMode operatingMode;
	enum LSM6DSO_GYRO_FS fullScale;
};

struct LSM6DSO{
	struct Acc acc;
	struct Gyro gyro;
};

extern struct LSM6DSO lsm6;








#endif /* SENSORS_IMU_H_ */
