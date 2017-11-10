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
#include "hal_entry.h"
#include "i2c.h"
#include "sht31.h"

static uint8_t  measure_data[6];

ssp_err_t readsht31status (uint16_t * result) {
    uint8_t   cmd[2];
    uint8_t   status_data[3];
    ssp_err_t err;

    cmd[0] = Status_CMD_MSB;
    cmd[1] = Status_CMD_LSB;
    err = g_ext_i2c_bus_write( cmd, 2, false);
    APP_ERROR_TRAP(err)

    if (err == SSP_SUCCESS) {		    
	err = g_ext_i2c_bus_read(status_data, 3, false);
        APP_ERROR_TRAP(err)
    }

    *result =  ((uint16_t) status_data[0]) << 8;	    
    *result |= ((uint16_t) status_data[1]);
    return (err); 
}

ssp_err_t readsht31_temperature_humidity (float *temperatureC,
                                     float *temperatureF,
                                     float *humidityP) {
    uint8_t   cmd[2];
    uint8_t   status_data[3];


    ssp_err_t err;

    cmd[0] = HT_CMD_MSB;
    cmd[1] = HT_CMD_LSB;
    err = g_ext_i2c_bus_write( cmd, 2, false);
    APP_ERROR_TRAP(err)


    if (err == SSP_SUCCESS) {
        delay(100);    // 100 msec delay

        // check for conversion completion
        err = g_ext_i2c_bus_read(measure_data, 6, false);
        APP_ERROR_TRAP(err)

        if (err == SSP_SUCCESS) {
            Temperature_Humidity_Conversion(&*temperatureC, &*temperatureF, &*humidityP);
        }
    }
    return (err);
}

void Temperature_Humidity_Conversion(float *temperatureC,
                                     float *temperatureF,
                                     float *humidityP
                                     ) {
    uint16_t temperature_raw;
    uint16_t humidity_raw;

    // Calculate the temperature in C and F
    temperature_raw = measure_data[0];
    temperature_raw = temperature_raw << (uint16_t) 8 ;
    temperature_raw = temperature_raw + (uint16_t) measure_data[1];
    *temperatureC = 175.0 * (float) temperature_raw / 65535.0;
    *temperatureC = *temperatureC - 45;

    *temperatureF = 315.0 * (float) temperature_raw / 65535.0;
    *temperatureF = *temperatureF - 49;

    if (*temperatureF == 0.0 || *temperatureC == 0.0){
        g_ioport.p_api->pinWrite(g_leds.p_leds[GRN],ON);
    }

    // Calculate the humidity in %
    humidity_raw      = measure_data[3];
    humidity_raw      = humidity_raw << (uint16_t) 8;
    humidity_raw      = humidity_raw + (uint16_t) measure_data[4];
    *humidityP = 100.0 * (float) humidity_raw / 65535.0;
}
