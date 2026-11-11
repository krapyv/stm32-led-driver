#ifndef LED_H
#define LED_H

#include <stdint.h>

// generic LED handle
typedef struct
{
    volatile uint32_t *moder_reg;   // pointer to the GPIO MODER register
    volatile uint32_t *odr_reg;     // pointer to the GPIO ODR register
    volatile uint32_t *bsrr_reg;    // pointer to the GPIO BSRR register (write-only register, so use assignment (=), not RMW (|=))
    volatile uint32_t *rcc_clk_reg; // pointer to the clock register
    uint32_t half_period_ms;        // blink/delay value
    volatile uint32_t counter;
    uint8_t pin;     // pin number (from 0 to 15)
    uint8_t rcc_bit; // bit position in RCC_AHB1ENR to enable the clock
} LED_HandleTypeDef;

void led_init(LED_HandleTypeDef *hled);
void led_on(LED_HandleTypeDef *hled);
void led_off(LED_HandleTypeDef *hled);
void led_on_bsrr(LED_HandleTypeDef *hled);
void led_off_bsrr(LED_HandleTypeDef *hled);

#endif