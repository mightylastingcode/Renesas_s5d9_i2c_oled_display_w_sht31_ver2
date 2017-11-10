/*
 *
 *    Author: Michael Li (Self - independent developer)
 *    Date: 10/27/2017
 *    Company: Self
 *    Project: Renesas S5D9 Tutorial.
 *
 *    Description:
 *
 *  Develop the C code from scratch forÂ the S5D9 board
 *
 *  Read the current temperature (F) from onboard AMS EN210 or SHT31 sensor (I2C interface).
 *  Display the current temperature (F) on OLED display (I2C interface).
 *  Display the temperature graphically over time on OLED display.
 *
 *
 */
#include "hal_data.h"

//  SHT31 Temperature and Humidity Sensor
#define SHT31_I2C_ADDRESS   0x44  // 011110+SA0+RW - 0x3C or 0x3D

#define Status_CMD_MSB 0xF3
#define Status_CMD_LSB 0x2D

#define HT_CMD_MSB 0x24     // Temperature and humidity read command
#define HT_CMD_LSB 0x00


ssp_err_t readstatus (uint16_t * result);
void Temperature_Humidity_Conversion(float *temperatureC,
                                     float *temperatureF,
                                     float *humidityP);
ssp_err_t read_temperature_humidity (float *temperatureC,
                                     float *temperatureF,
                                     float *humidityP);
