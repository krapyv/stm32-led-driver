#include "led.h"
#include <stdbool.h>

void led_init(LED_HandleTypeDef *hled)
{
    // first of all, enable a clock
    *hled->rcc_clk_reg |= (1u << hled->rcc_bit);

    // next set according bits in MODER to 01 (output)
    // MODER operates on two bits, so 1 bit = 2 * pin and 2 bit = (2 * pin) + 1

    // clear the bits first
    *hled->moder_reg &= ~((0x3u << (2 * hled->pin))); // 0x3 = 0b0011 -> after invert: 0b1100

    // now set to 01
    // 0x1 = 0b001

    *hled->moder_reg |= (0x1u << (2 * hled->pin));
}

void led_on(LED_HandleTypeDef *hled)
{
    // special case: PC13, active low - driving the pin low turns it on
    if ((hled->pin == 13) && (hled->rcc_bit == 2))
    {
        *hled->odr_reg &= ~(1U << hled->pin);
    }
    else
    {
        // next we need to set the value HIGH to the GPIO_ODR of the pin
        // since we are using external LED, not the PC13 one, the value 1 is HIGH (3.3V) and 0 is LOW (0V)

        *hled->odr_reg |= (1U << hled->pin);
    }
}

void led_off(LED_HandleTypeDef *hled)
{
    if ((hled->pin == 13) && (hled->rcc_bit == 2))
    {
        *hled->odr_reg |= (1U << hled->pin);
    }
    else
    {
        *hled->odr_reg &= ~(1U << hled->pin); // we want to keep all existing bits and clear the bit PIN, so AND with NOT (~)
    }
}

void led_on_bsrr(LED_HandleTypeDef *hled)
{
    // special case: PC13, active low - driving the pin low turns it on
    // PC13 is active-low
    // inverted: ON = 0, OFF = 1
    if ((hled->pin == 13) && (hled->rcc_bit == 2))
    {
        // ON = 0
        // bits 31:16
        *hled->bsrr_reg = (1U << (hled->pin + 16));
    }
    else
    {
        *hled->bsrr_reg = (1U << hled->pin);
    }
}

void led_off_bsrr(LED_HandleTypeDef *hled)
{
    // PC13 is active-low
    // inverted: ON = 0, OFF = 1
    if ((hled->pin == 13) && (hled->rcc_bit == 2))
    {
        // OFF = 1
        *hled->bsrr_reg = (1U << hled->pin);
    }
    else
    {
        // bits 31:16
        // pin 0 - bit 16, 5 - 21, 15 - bit 31
        *hled->bsrr_reg = (1U << (hled->pin + 16));
    }
}