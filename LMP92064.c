#include "LMP92064.h"
#include "nrf_drv_spi.h"

/// @warning CURRENT MUST BE READ BEFORE VOLTAGE, IN ORDER!

/**
 * @brief 	query ADC over SPI to get a voltage reading in volts (blocking)
 * @param 	spiPtr: handle for an already setup SPI peripheral
 * @retval 	voltage: voltage in volts
*/
float LMP_getVoltage(const nrf_drv_spi_t *spiPtr) {
	uint16_t txBuf = 0;
	uint8_t rxBuf = 0;

	uint16_t voltageWord = 0;
	float voltage = 0;

	txBuf = DATA_VOUT_MSB | READ_BIT;                                 				// pull MSB, set MSBit to read
	txBuf = (txBuf >> 8) | (txBuf << 8);											// swap byte order to big endian
	nrf_drv_spi_transfer(spiPtr, (uint8_t*)&txBuf, TRANSFER_OUT_SIZE, NULL, 0);		// write cmd
	nrf_drv_spi_transfer(spiPtr, NULL, 0, (uint8_t*)&rxBuf, TRANSFER_IN_SIZE);		// read voltage MSB
	voltageWord += (rxBuf << 8) & 0x0F;												// set upper byte (12 bit ADC so only 4 bits here)

	txBuf = DATA_VOUT_LSB | READ_BIT;                                    			// pull LSB, set MSBit to read
	txBuf = (txBuf >> 8) | (txBuf << 8);											// swap byte order to big endian
	nrf_drv_spi_transfer(spiPtr, (uint8_t*)&txBuf, TRANSFER_OUT_SIZE, NULL, 0);		// write cmd
	nrf_drv_spi_transfer(spiPtr, NULL, 0, (uint8_t*)&rxBuf, TRANSFER_IN_SIZE);		// read voltage LSB
	voltageWord += rxBuf;															// set lower byte

	voltage = voltageWord * ADC_VOLTS_PER_BIT;										// convert to a decimal value

	return voltage;
}

/**
 * @brief 	query ADC over SPI to get a current reading in milliAmps (blocking)
 * @param 	spiPtr: handle for an already setup SPI peripheral
 * @retval 	currentmA: current in mA
*/
float LMP_getCurrent(const nrf_drv_spi_t *spiPtr) {
	uint16_t txBuf = 0;
	uint8_t rxBuf = 0;

	uint16_t currentWord = 0;
	float currentmA = 0;

	txBuf = DATA_COUT_MSB | READ_BIT;                                 				// pull MSB, set MSBit to read
	txBuf = (txBuf >> 8) | (txBuf << 8);											// swap byte order to big endian
	nrf_drv_spi_transfer(spiPtr, (uint8_t*)&txBuf, TRANSFER_OUT_SIZE, NULL, 0);		// write cmd
	nrf_drv_spi_transfer(spiPtr, NULL, 0, (uint8_t*)&rxBuf, TRANSFER_IN_SIZE);		// read current MSB
	currentWord += (rxBuf << 8) & 0x0F;												// set upper byte (12 bit ADC so only 4 bits here)

	txBuf = DATA_COUT_LSB | READ_BIT;                                    			// pull LSB, set MSBit to read
	txBuf = (txBuf >> 8) | (txBuf << 8);											// swap byte order to big endian
	nrf_drv_spi_transfer(spiPtr, (uint8_t*)&txBuf, TRANSFER_OUT_SIZE, NULL, 0);		// write cmd
	nrf_drv_spi_transfer(spiPtr, NULL, 0, (uint8_t*)&rxBuf, TRANSFER_IN_SIZE);		// read current LSB
	currentWord += rxBuf;															// set lower byte

	currentmA = currentWord * ADC_MA_PER_BIT;										// convert to a decimal value

	return currentmA;
}
