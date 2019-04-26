#include <stdint.h>

#include <GPIO/GPIO.h>
#include <dmb_delay_systick.h>

#include <libs_config/HD44780_settings.h>


static void __attribute__((optimize("O0"))) del(uint32_t x)
{
	while(x--);
}

void _HD44780HAL_init_RW(void)
{
#ifdef HD44780_USE_BUSY_FLAG
	GPIO_InitOutput(LCD_RW_GPIO_CONFIG);
#endif
}

void HD44780HAL_init_GPIO(void)
{
	GPIO_InitOutput(LCD_RS_GPIO_CONFIG);
	GPIO_InitOutput(LCD_E_GPIO_CONFIG);

	_HD44780HAL_init_RW();

	GPIO_InitOutput(LCD_DB4_GPIO_CONFIG);
	GPIO_InitOutput(LCD_DB5_GPIO_CONFIG);
	GPIO_InitOutput(LCD_DB6_GPIO_CONFIG);
	GPIO_InitOutput(LCD_DB7_GPIO_CONFIG);
}

void HD44780HAL_E_high(void)
{
	GPIO_SetHigh(LCD_E_GPIO_CONFIG);
}

void HD44780HAL_E_low(void)
{
	GPIO_SetLow(LCD_E_GPIO_CONFIG);
}

void HD44780HAL_RS_high(void)
{
	GPIO_SetHigh(LCD_RS_GPIO_CONFIG);
}

void HD44780HAL_RS_low(void)
{
	GPIO_SetLow(LCD_RS_GPIO_CONFIG);
}

void HD44780HAL_RW_high(void)
{
#ifdef HD44780_USE_BUSY_FLAG
	GPIO_SetHigh(LCD_RW_GPIO_CONFIG);
#endif
}

void HD44780HAL_RW_low(void)
{
#ifdef HD44780_USE_BUSY_FLAG
	GPIO_SetLow(LCD_RW_GPIO_CONFIG);
#endif
}

void HD44780HAL_DB4_high(void)
{
	GPIO_SetHigh(LCD_DB4_GPIO_CONFIG);
}

void HD44780HAL_DB4_low(void)
{
	GPIO_SetLow(LCD_DB4_GPIO_CONFIG);
}

void HD44780HAL_DB5_high(void)
{
	GPIO_SetHigh(LCD_DB5_GPIO_CONFIG);
}

void HD44780HAL_DB5_low(void)
{
	GPIO_SetLow(LCD_DB5_GPIO_CONFIG);
}

void HD44780HAL_DB6_high(void)
{
	GPIO_SetHigh(LCD_DB6_GPIO_CONFIG);
}

void HD44780HAL_DB6_low(void)
{
	GPIO_SetLow(LCD_DB6_GPIO_CONFIG);
}

void HD44780HAL_DB7_high(void)
{
	GPIO_SetHigh(LCD_DB7_GPIO_CONFIG);
}

void HD44780HAL_DB7_low(void)
{
	GPIO_SetLow(LCD_DB7_GPIO_CONFIG);
}

uint8_t HD44780HAL_read_DB4(void)
{
	return GPIO_InputState(LCD_DB4_GPIO_CONFIG);
}

uint8_t HD44780HAL_read_DB5(void)
{
	return GPIO_InputState(LCD_DB5_GPIO_CONFIG);
}

uint8_t HD44780HAL_read_DB6(void)
{
	return GPIO_InputState(LCD_DB6_GPIO_CONFIG);
}

uint8_t HD44780HAL_read_DB7(void)
{
	return GPIO_InputState(LCD_DB7_GPIO_CONFIG);
}

void HD44780HAL_DB_pins_output(void)
{
#ifdef HD44780_USE_BUSY_FLAG
	GPIO_InitOutput(LCD_DB4_GPIO_CONFIG);
	GPIO_InitOutput(LCD_DB5_GPIO_CONFIG);
	GPIO_InitOutput(LCD_DB6_GPIO_CONFIG);
	GPIO_InitOutput(LCD_DB7_GPIO_CONFIG);
#endif
}

void HD44780HAL_DB_pins_input(void)
{
#ifdef HD44780_USE_BUSY_FLAG
	GPIO_InitInput(LCD_DB4_GPIO_CONFIG);
	GPIO_InitInput(LCD_DB5_GPIO_CONFIG);
	GPIO_InitInput(LCD_DB6_GPIO_CONFIG);
	GPIO_InitInput(LCD_DB7_GPIO_CONFIG);
#endif
}

void HD44780HAL_delay_ms(uint8_t ms)
{
	_delay_ms(ms);
}

void HD44780HAL_delay_us(uint8_t us)
{
	del(us);
}
