#ifndef HD44780_HD44780_HAL_H_
#define HD44780_HD44780_HAL_H_

#include <stdint.h>

void HD44780HAL_init_GPIO(void);

void HD44780HAL_E_high(void);
void HD44780HAL_E_low(void);

void HD44780HAL_RS_high(void);
void HD44780HAL_RS_low(void);

void HD44780HAL_RW_high(void);
void HD44780HAL_RW_low(void);

void HD44780HAL_DB4_high(void);
void HD44780HAL_DB4_low(void);

void HD44780HAL_DB5_high(void);
void HD44780HAL_DB5_low(void);

void HD44780HAL_DB6_high(void);
void HD44780HAL_DB6_low(void);

void HD44780HAL_DB7_high(void);
void HD44780HAL_DB7_low(void);

uint8_t HD44780HAL_read_DB4(void);

uint8_t HD44780HAL_read_DB5(void);

uint8_t HD44780HAL_read_DB6(void);

uint8_t HD44780HAL_read_DB7(void);

void HD44780HAL_DB_pins_output(void);
void HD44780HAL_DB_pins_input(void);

void HD44780HAL_delay_ms(uint8_t ms);
void HD44780HAL_delay_us(uint8_t us);

#endif /* HD44780_HD44780_HAL_H_ */
