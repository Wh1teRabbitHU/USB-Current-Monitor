#include "adc.h"

void ADC_init(I2C_HandleTypeDef* handler) {
    HAL_I2C_Init(handler);
    ADC_writeConfig(handler, 0b00011000);
}

uint8_t ADC_readConfig(I2C_HandleTypeDef* handler) {
    uint8_t readBuffer[3] = {0};
    HAL_StatusTypeDef result = HAL_I2C_Master_Receive(handler, ADC_I2C_ADDR, readBuffer, 3, 100);

    if (result != HAL_OK) {
        return result;
    }

    return readBuffer[2];
}

uint8_t ADC_writeConfig(I2C_HandleTypeDef* handler, uint8_t config) {
    uint8_t writeBuffer[1] = {config};
    volatile HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(handler, ADC_I2C_ADDR, writeBuffer, 1, 100);

    if (result != HAL_OK) {
        return 0;
    }

    return 1;
}

uint32_t ADC_readData(I2C_HandleTypeDef* handler) {
    uint8_t readBuffer[3] = {0};
    HAL_StatusTypeDef result = HAL_I2C_Master_Receive(handler, ADC_I2C_ADDR, readBuffer, 3, 100);

    if (result != HAL_OK) {
        return result;
    }

    // return (readBuffer[0] << 16) | (readBuffer[1] << 8) | readBuffer[2];
    return (readBuffer[0] << 8) | readBuffer[1];
}

double ADC_readVoltage(I2C_HandleTypeDef* handler) {
    HAL_GPIO_WritePin(MUX_A0_GPIO_Port, MUX_A0_Pin, 0);
    HAL_GPIO_WritePin(MUX_A1_GPIO_Port, MUX_A1_Pin, 1);

    HAL_Delay(200);

    uint32_t rawData = ADC_readData(handler);

    return (rawData * MEASUREMENT_UNIT * VOLTAGE_MULTIPLIER) / 1000;
}

double ADC_readCurrent(I2C_HandleTypeDef* handler) {
    HAL_GPIO_WritePin(MUX_A0_GPIO_Port, MUX_A0_Pin, 0);
    HAL_GPIO_WritePin(MUX_A1_GPIO_Port, MUX_A1_Pin, 0);

    HAL_Delay(200);

    uint32_t rawData = ADC_readData(handler);

    return ((rawData * MEASUREMENT_UNIT) / CURRENT_OPAMP_GAIN) / CURRENT_01_R;
}