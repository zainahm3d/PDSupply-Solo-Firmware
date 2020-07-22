/**
 * @file PDSupply.h
 * @brief This file provides pin names, status/command structs, and status/command definitions for PDSuppy
 * @author Zain Ahmed
*/

#ifndef PDSUPPLY_H
#define PDSUPPLY_H

typedef __uint8_t uint8_t;
typedef __uint32_t uint32_t;

// Possible values for SupplyData_struct.status
#define PD_STATUS_OUTPUT_GOOD			0x0A
#define PD_STATUS_OUTPUT_OFF			0x0B
#define PD_STATUS_OUTPUT_OVERCURRENT	0x0C
#define PD_STATUS_OUTPUT_HIGH			0x0D
#define PD_STATUS_OUTPUT_LOW			0x0E

// Possible values for MasterData_struct_struct.commandedStatus
#define PD_COMMAND_OUTPUT_ON			0x1A
#define PD_COMMAND_OUTPUT_OFF			0x1B
#define PD_COMMAND_OUTPUT_KEEP_STATE	0x1C
#define PD_COMMAND_LED_ON				0x1D
#define PD_COMMAND_LED_OFF				0x1E

// Supply to Master, 16 BYTES
struct SupplyData_struct {
	uint32_t counter;
	uint32_t status;
	float measuredVoltage;
	float measuredCurrent;
};

// Master to Supply, 16 BYTES
struct MasterData_struct {
	uint32_t commandedStatus;
	uint32_t commandedOutput;
	float commandedVoltage;
	float commandedCurrent;
};

// LED GPIOs
#define PD_BLE_CONNECTED_LED 			NRF_GPIO_PIN_MAP(0, 15)
#define PD_BLE_ACTIVITY_LED 			NRF_GPIO_PIN_MAP(0, 14)

// Auxillary test pin used for time measurement/etc (not exposed on PDSupply PCB)
#define TEST_PIN NRF_GPIO_PIN_MAP(1, 0)

// SPI Pins
#define PD_MISO_PIN 					NRF_GPIO_PIN_MAP(0, 4)
#define PD_MOSI_PIN 					NRF_GPIO_PIN_MAP(0, 6)
#define PD_SCK_PIN 						NRF_GPIO_PIN_MAP(0, 5)
#define PD_LMP92064_CS_PIN 				NRF_GPIO_PIN_MAP(0, 7)

// STUSB Pins
#define STUSB_RESET_PIN					NRF_GPIO_PIN_MAP(0, 11)

#endif // PDSUPPLY_H
