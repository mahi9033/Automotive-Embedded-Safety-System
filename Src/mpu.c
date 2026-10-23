#include "mpu.h"
#include "i2c.h"

static void mpu_write(uint8_t reg, uint8_t value)
{
    i2c_write_byte(MPU6050_ADDR, reg, &value);
}

int MPU6050_Init(void)
{
    uint8_t id = 0;

    /*  Check the device is present */
    i2c_read_burst(MPU6050_ADDR, MPU6050_REG_WHO_AM_I, &id, 1);
    if (id != MPU6050_WHO_AM_I_VAL)
    {
        return -1;
    }

    /*  Wake up, clock = PLL with X gyro */
    mpu_write(MPU6050_REG_PWR_MGMT_1, 0x01U);

    /*  DLPF on (~44 Hz accel / 42 Hz gyro): gyro rate becomes 1 kHz */
    mpu_write(MPU6050_REG_CONFIG, 0x03U);

    /*  Sample rate = 1 kHz / (1 + 9) = 100 Hz */
    mpu_write(MPU6050_REG_SMPLRT_DIV, 9U);

    /* Full-scale ranges: gyro +-250 deg/s, accel +-2 g */
    mpu_write(MPU6050_REG_GYRO_CFG, 0x00U);
    mpu_write(MPU6050_REG_ACCEL_CFG, 0x00U);

    return 0;
}

void MPU6050_ReadRaw(MPU6050_Raw_t *raw)
{
    uint8_t b[14];

    i2c_read_burst(MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT, b, 14);

    raw->ax   = (int16_t)((b[0]  << 8) | b[1]);
    raw->ay   = (int16_t)((b[2]  << 8) | b[3]);
    raw->az   = (int16_t)((b[4]  << 8) | b[5]);
    raw->temp = (int16_t)((b[6]  << 8) | b[7]);
    raw->gx   = (int16_t)((b[8]  << 8) | b[9]);
    raw->gy   = (int16_t)((b[10] << 8) | b[11]);
    raw->gz   = (int16_t)((b[12] << 8) | b[13]);
}

void MPU6050_ReadScaled(MPU6050_Data_t *data)
{
    MPU6050_Raw_t r;
    MPU6050_ReadRaw(&r);

    data->ax = r.ax / MPU6050_ACCEL_LSB_PER_G;
    data->ay = r.ay / MPU6050_ACCEL_LSB_PER_G;
    data->az = r.az / MPU6050_ACCEL_LSB_PER_G;

    data->gx = r.gx / MPU6050_GYRO_LSB_PER_DPS;
    data->gy = r.gy / MPU6050_GYRO_LSB_PER_DPS;
    data->gz = r.gz / MPU6050_GYRO_LSB_PER_DPS;

    data->temp_c = (r.temp / 340.0f) + 36.53f;
}
