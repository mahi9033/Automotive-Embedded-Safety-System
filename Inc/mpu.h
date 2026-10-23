/*
 * mpu.h
 *
 *  Created on: Oct 14, 2026
 *      Author: Mahi
 */

#ifndef MPU_H_
#define MPU_H_
#include "i2c.h"
#include "stm32f4xx.h"
#include <stdint.h>

/* 7-bit I2C address (AD0 = GND). Use 0x69 if AD0 = VCC. */
#define MPU6050_ADDR            0x68U

/* Register map */
#define MPU6050_REG_SMPLRT_DIV  0x19U
#define MPU6050_REG_CONFIG      0x1AU
#define MPU6050_REG_GYRO_CFG    0x1BU
#define MPU6050_REG_ACCEL_CFG   0x1CU
#define MPU6050_REG_ACCEL_XOUT  0x3BU   /* start of 14-byte data block */
#define MPU6050_REG_PWR_MGMT_1  0x6BU
#define MPU6050_REG_WHO_AM_I    0x75U

#define MPU6050_WHO_AM_I_VAL    0x68U

/* Sensitivity at default ranges (+-2 g, +-250 deg/s) */
#define MPU6050_ACCEL_LSB_PER_G     16384.0f
#define MPU6050_GYRO_LSB_PER_DPS    131.0f

typedef struct {
    int16_t ax, ay, az;
    int16_t temp;
    int16_t gx, gy, gz;
} MPU6050_Raw_t;

typedef struct {
    float ax, ay, az;     /* g */
    float gx, gy, gz;     /* deg/s */
    float temp_c;         /* deg C */
} MPU6050_Data_t;

/* Returns 0 on success, -1 if the sensor is not found */
int  MPU6050_Init(void);
void MPU6050_ReadRaw(MPU6050_Raw_t *raw);
void MPU6050_ReadScaled(MPU6050_Data_t *data);



#endif /* MPU_H_ */
