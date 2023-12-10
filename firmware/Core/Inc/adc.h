#ifndef __ADC_H
#define __ADC_H

#include "main.h"

#define ADC_I2C_ADDR (0b1101000 << 1)

#define VOLTAGE_MULTIPLIER (5 / 0.652)
#define CURRENT_01_MULTIPLIER (5 / 0.652)
#define CURRENT_02_MULTIPLIER (5 / 0.652)
#define MEASUREMENT_UNIT 0.0625  // in mV one bit

void ADC_init(I2C_HandleTypeDef* handler);
uint8_t ADC_readConfig(I2C_HandleTypeDef* handler);
uint8_t ADC_writeConfig(I2C_HandleTypeDef* handler, uint8_t config);
uint32_t ADC_readData(I2C_HandleTypeDef* handler);

double ADC_readVoltage(I2C_HandleTypeDef* handler);
double ADC_readCurrent(I2C_HandleTypeDef* handler);

#endif