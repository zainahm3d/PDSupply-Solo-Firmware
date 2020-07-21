#ifndef LMP92064_H
#define LMP92064_H

#include "nrf_drv_spi.h"

// ADC specs
#define ADC_FS_V        	2.048		// in volts
#define ADC_FS_C        	81.92		// in millivolts
#define ADC_NUM_STEPS		4096		// 2^12

// for conversions to real values
#define ADC_VOLTS_PER_BIT 	ADC_FS_V / ADC_NUM_STEPS
#define ADC_MA_PER_BIT		ADC_FS_C / ADC_NUM_STEPS

// ADC control and output register layout
// RW: MSBit of address is R/W ctrl.
#define CONFIG_A 			(uint16_t)0x0000
#define CONFIG_B 			(uint16_t)0x0001
#define REG_UPDATE 			(uint16_t)0x000F
#define CONFIG_REG 			(uint16_t)0x0100
#define STATUS 				(uint16_t)0x0103

// Transmitted MSB first by default
#define DATA_VOUT_LSB 		(uint16_t)0x0200
#define DATA_VOUT_MSB 		(uint16_t)0x0201

// Transmitted MSB first by default
#define DATA_COUT_LSB 		(uint16_t)0x0202
#define DATA_COUT_MSB 		(uint16_t)0x0203

// SPI R/W controls
#define READ_BIT        	(uint16_t)1 << 15
#define WRITE_BIT       	(uint16_t)0 << 15

// SPI bytes per transfer
#define TRANSFER_IN_SIZE    (uint8_t)1
#define TRANSFER_OUT_SIZE   (uint8_t)2

// Function Prototypes
float LMP_getVoltage();
float LMP_getCurrent();
void LMP_readRegisters(const nrf_drv_spi_t *spiPtr);


#endif // LMP92064_H
