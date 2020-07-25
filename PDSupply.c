#include "PDSupply.h"
#include "nrf_drv_WS2812.h"
#include "nrf_gpio.h"
#include "nrf_drv_pwm.h"

static nrf_drv_pwm_t m_pwm1 = NRF_DRV_PWM_INSTANCE(1);

// Declare variables holding PWM sequence values. In this example only one channel is used
nrf_pwm_values_individual_t seq_values[] = {0, 0, 0, 0};
nrf_pwm_sequence_t const seq =
{
    .values.p_individual = seq_values,
    .length          = NRF_PWM_VALUES_LENGTH(seq_values),
    .repeats         = 0,
    .end_delay       = 0
};


static void pwm_init(void)
{
    nrf_drv_pwm_config_t const config0 =
    {
        .output_pins =
        {
            DACA_PIN,                             // channel 0
            NRF_DRV_PWM_PIN_NOT_USED,             // channel 1
            NRF_DRV_PWM_PIN_NOT_USED,             // channel 2
            NRF_DRV_PWM_PIN_NOT_USED,             // channel 3
        },
        .irq_priority = APP_IRQ_PRIORITY_LOWEST,
        .base_clock   = NRF_PWM_CLK_1MHz,
        .count_mode   = NRF_PWM_MODE_UP,
        .top_value    = 1000,
        .load_mode    = NRF_PWM_LOAD_INDIVIDUAL,
        .step_mode    = NRF_PWM_STEP_AUTO
    };
    // Init PWM without error handler
    APP_ERROR_CHECK(nrf_drv_pwm_init(&m_pwm1, &config0, NULL));

}

void initPD() {
    pwm_init();

    nrf_gpio_cfg_output(BUCK_ENABLE);
	nrf_gpio_cfg_output(RELAY_PIN);
}

// Set duty cycle between 0 and 100%
void pwm_update_duty_cycle(float duty_cycle)
{
    duty_cycle = duty_cycle * 10;
    // Check if value is outside of range. If so, set to 100%
    if(duty_cycle >= 1000)
    {
        seq_values->channel_0 = (uint16_t)1000;
    }
    else
    {
        seq_values->channel_0 = (uint16_t)duty_cycle;
    }

    nrf_drv_pwm_simple_playback(&m_pwm1, &seq, 1, NRF_DRV_PWM_FLAG_LOOP);
}

void updateStatusLed(struct SupplyData_struct s)
{
    switch (s.status)
    {
        case PD_STATUS_OUTPUT_GOOD:
            nrf_drv_WS2812_set_pixel(STATUS_LED, COLOR_GREEN);
            break;

        case PD_STATUS_OUTPUT_OFF:
            nrf_drv_WS2812_set_pixel(STATUS_LED, COLOR_YELLOW);
            break;

        default:
			nrf_drv_WS2812_set_pixel(STATUS_LED, COLOR_RED);
            break;
    }

    nrf_drv_WS2812_show();
}

void setVoltage(float voltage)
{
    voltage += 0.5; // this line is garbage. TESTING ONLY

    // Calculate feedback voltage using voltage divider equation
    // (Vs * R2) / (R1 + R2)
    double vFB = (voltage * PD_R2_VAL) / (PD_R1_VAL + PD_R2_VAL);

    // calculate necessary duty cycle (in percent) to get desired vFB
    // vout = (dutyCycle / 100) * vFB
    float dutyCycle = (vFB / PD_BUCK_FB_MAX_V) * 100;

    pwm_update_duty_cycle((float)100 - dutyCycle);
}