# Renesas_s5d9_i2c_oled_display_w_sht31_ver2
Add an external I2C SHT31 temperature and humidity sensor.   Version 2 has a number of improvements (all 26 letters (A-Z)  are supported and message display method is simpler).

Develop the C code from scratch for the S5D9 board
Read the current temperature (F) from an external SHT31 sensor (I2C interface).
Display the current temperature (F) on OLED display (I2C interface).
Display the temperature graphically over time on OLED display.

File Description:
1.  hal_entry.c/h  (Main Program Loop)
2.  i2c.c/h (i2c SSP API calls)
3   sht31.c/h (subroutines for interfacing with the sht31 sensor)
4.  ssd1306_oled.c/h (subroutines for the OLED module operations)
5.  en210.c/h (subroutines for AMS EN210 operations - not used in this tutorial but kept here.)

6. S5D9_I2C_INT_ENV210_OLED_SHT31.7z (7zip archive file for e2 studio project file for this project)  Unzip and import into your e2 studio.  It is ready to run if you cannot make your project to work

Datasheet:
SENSIRION SHT3x-DIS 314010179_SMD Temperature and Humidity Sensor Datasheets.pdf (Temperature sensor datasheet)
OLED Sepecification.pdf (OLED display module spec sheet)
SSD1306.pdf (OLED display driver chip datasheet)

https://www.miketechuniverse.com/single-post/2017/10/30/I2C-Tutorial-for-Renesas-S5D9-board-Add-an-External-SHT31-sensor-Part2
