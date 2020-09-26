/**
 * @file PDSupply.h
 * @brief This file provides pin names, status/command structs, and status/command definitions for PDSupply
 * @author Zain Ahmed
*/

#ifndef PDSUPPLY_H
#define PDSUPPLY_H

#include <stdint.h>

// typedef __uint8_t uint8_t;
// typedef __uint32_t uint32_t;

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

// PWM DAC Pins
#define DACA_PIN						NRF_GPIO_PIN_MAP(0, 2)
#define DACB_PIN						NRF_GPIO_PIN_MAP(0, 3)

// Photorelay Pin
#define RELAY_PIN						NRF_GPIO_PIN_MAP(0, 14)

// Main buck enable
#define BUCK_ENABLE						NRF_GPIO_PIN_MAP(0, 8)

// Main buck voltage calc equations
#define PD_R1_VAL						(uint32_t)249000
#define PD_R2_VAL						(uint32_t)15000
#define PD_BUCK_FB_MAX_V				(float)0.7

// RGB LEDs
#define PIXEL_PIN 						21
#define BLE_LED							1
#define STATUS_LED						0
#define COLOR_GREEN						0, 50, 0
#define COLOR_RED						50, 0, 0
#define COLOR_YELLOW					50, 50, 0
#define COLOR_OFF						0, 0, 0

// Function prototypes
void updateStatusLed(struct SupplyData_struct s);
void setVoltage(float voltage);
void pwm_update_duty_cycle(float duty_cycle);
void initPD();

#endif // PDSUPPLY_H
