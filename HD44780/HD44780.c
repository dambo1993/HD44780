//-------------------------------------------------------------------------------------------------
// Wyúwietlacz alfanumeryczny ze sterownikiem HD44780
// Sterowanie w trybie 4-bitowym bez odczytu flagi zajÍtoúci
// z dowolnym przypisaniem sygna≥Ûw sterujπcych
// Plik : HD44780.c	
// Mikrokontroler : Atmel AVR
// Kompilator : avr-gcc
// Autor : Rados≥aw KwiecieÒ
// èrÛd≥o : http://radzio.dxp.pl/hd44780/
// Data : 24.03.2007
// Modify by dambo - http://projektydmb.blogspot.com/
//-------------------------------------------------------------------------------------------------

#include "HD44780.h"
#include "HD44780_hal.h"

#include <libs_config/HD44780_settings.h>


//-------------------------------------------------------------------------------------------------
//
// Funkcja odczytujaca pÛ≥bajt z magistrali danych
//
//-------------------------------------------------------------------------------------------------
static unsigned char _LCD_InNibble(void)
{
	unsigned char tmp = 0;

	if(HD44780HAL_read_DB4())
		tmp |= (1 << 0);
	if(HD44780HAL_read_DB5())
		tmp |= (1 << 1);
	if(HD44780HAL_read_DB6())
		tmp |= (1 << 2);
	if(HD44780HAL_read_DB7())
		tmp |= (1 << 3);
	return tmp;
}

//-------------------------------------------------------------------------------------------------
//
// Funkcja odczytu bajtu z wyúwietacza (bez rozrÛønienia instrukcja/dane).
//
//-------------------------------------------------------------------------------------------------
unsigned char _LCD_Read(void)
{
	unsigned char tmp = 0;

	HD44780HAL_DB_pins_input();

	HD44780HAL_RW_high();
	HD44780HAL_E_high();
	tmp |= (_LCD_InNibble() << 4);
	HD44780HAL_E_low();

	HD44780HAL_E_high();
	tmp |= _LCD_InNibble();
	HD44780HAL_E_low();

	return tmp;
}

//-------------------------------------------------------------------------------------------------
//
// Funkcja odczytu bajtu statusowego
//
//-------------------------------------------------------------------------------------------------
static unsigned char LCD_ReadStatus(void)
{
	HD44780HAL_RS_low();
	return _LCD_Read();
}

//-------------------------------------------------------------------------------------------------
//
// Oczekiwanie na wyswietlacz po przeslaniu danych
//
//-------------------------------------------------------------------------------------------------
static inline void _LCD_wait_after_command(void)
{
#ifdef HD44780_USE_BUSY_FLAG
	while(LCD_ReadStatus() & 0x80);
#else
	HD44780HAL_delay_us(50);
#endif
}

//-------------------------------------------------------------------------------------------------
//
// Funkcja wystawiajπca pÛ≥bajt na magistralÍ danych
//
//-------------------------------------------------------------------------------------------------
static void _LCD_OutNibble(unsigned char nibbleToWrite)
{
if(nibbleToWrite & 0x01)
	HD44780HAL_DB4_high();
else
	HD44780HAL_DB4_low();

if(nibbleToWrite & 0x02)
	HD44780HAL_DB5_high();
else
	HD44780HAL_DB5_low();

if(nibbleToWrite & 0x04)
	HD44780HAL_DB6_high();
else
	HD44780HAL_DB6_low();

if(nibbleToWrite & 0x08)
	HD44780HAL_DB7_high();
else
	HD44780HAL_DB7_low();
}

//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu bajtu do wyúwietacza (bez rozrÛønienia instrukcja/dane).
//
//-------------------------------------------------------------------------------------------------
static void _LCD_Write(unsigned char dataToWrite)
{
	HD44780HAL_DB_pins_output();

	HD44780HAL_RW_low();

	HD44780HAL_E_high();
	_LCD_OutNibble(dataToWrite >> 4);
	HD44780HAL_E_low();
//	HD44780HAL_delay_us(50);
	HD44780HAL_E_high();
	_LCD_OutNibble(dataToWrite);
	HD44780HAL_E_low();

	_LCD_wait_after_command();
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu rozkazu do wyúwietlacza
//
//-------------------------------------------------------------------------------------------------
void LCD_WriteCommand(unsigned char commandToWrite)
{
	HD44780HAL_RS_low();
	_LCD_Write(commandToWrite);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu danych do pamiÍci wyúwietlacza
//
//-------------------------------------------------------------------------------------------------
void LCD_WriteData(unsigned char dataToWrite)
{
	HD44780HAL_RS_high();
	_LCD_Write(dataToWrite);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja wyúwietlenia napisu na wyswietlaczu.
//
//-------------------------------------------------------------------------------------------------
void LCD_WriteText(char * text)
{
	while(*text)
	  LCD_WriteData(*text++);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja ustawienia wspÛ≥rzÍdnych ekranowych
//
//-------------------------------------------------------------------------------------------------
void LCD_GoTo(unsigned char x, unsigned char y)
{
	LCD_WriteCommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja czyszczenia ekranu wyúwietlacza.
//
//-------------------------------------------------------------------------------------------------
void LCD_Clear(void)
{
	LCD_WriteCommand(HD44780_CLEAR);
//	HD44780HAL_delay_ms(2);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja przywrÛcenia poczπtkowych wspÛ≥rzÍdnych wyúwietlacza.
//
//-------------------------------------------------------------------------------------------------
void LCD_Home(void)
{
	LCD_WriteCommand(HD44780_HOME);
	HD44780HAL_delay_ms(2);
}
//-------------------------------------------------------------------------------------------------
//
// Procedura inicjalizacji kontrolera HD44780.
//
//-------------------------------------------------------------------------------------------------
void LCD_Initalize(void)
{
	HD44780HAL_init_GPIO();
	HD44780HAL_delay_ms(15); // oczekiwanie na ustalibizowanie siÍ napiecia zasilajacego

	HD44780HAL_RS_low();
	HD44780HAL_E_low();
	HD44780HAL_RW_low();

	for(uint_fast8_t i = 0; i < 3; i++) // trzykrotne powtÛrzenie bloku instrukcji
	{
		HD44780HAL_E_high();
		_LCD_OutNibble(0x03); // tryb 8-bitowy
		HD44780HAL_E_low();
		HD44780HAL_delay_ms(5); // czekaj 5ms
	}

	HD44780HAL_E_high();
	_LCD_OutNibble(0x02); // tryb 4-bitowy
	HD44780HAL_E_low();

	HD44780HAL_delay_ms(1);
	LCD_WriteCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); // interfejs 4-bity, 2-linie, znak 5x7
	LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); // wy≥πczenie wyswietlacza
	LCD_Clear();
	LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT); // inkrementaja adresu i przesuwanie kursora
	LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK); // w≥πcz LCD, bez kursora i mrugania
}

//-------------------------------------------------------------------------------------------------
//
// Koniec pliku HD44780.c
//
//-------------------------------------------------------------------------------------------------
