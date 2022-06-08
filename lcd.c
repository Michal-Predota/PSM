#include "lcd.h"

void lcd_write_instr(uint8_t data)
{
	//zapis starszej połówki
	LCD_PORT&=~(1<<LCD_RS);//ustawienie zera w porcie LCD_PORT na pozycji RS
	
	LCD_PORT|=(1<<LCD_E);//ustawienie jedynki na pozycji E w LCD_PORT
	
	LCD_PORT = (data&0xf0)|(LCD_PORT&0x0f);//zerowanie czterech najmłodszych bitów w data i czterech najstarszych bitów w LCD_PORT
	
	_delay_ms(1);
	
	LCD_PORT&=~(1<<LCD_E);
	
	_delay_ms(1);
	//ustawienie młodszej połówki
	
	LCD_PORT|=(1<<LCD_E);
	
	LCD_PORT = (data<<4)|(LCD_PORT&0x0f);//4 młode bity zastępują starsze
	
	_delay_ms(1);
	
	LCD_PORT&=~(1<<LCD_E);
	
	_delay_ms(1);
}


void lcd_write_data(uint8_t data)
{
	LCD_PORT|=(1<<LCD_RS);
	
	LCD_PORT|=(1<<LCD_E);
	
	LCD_PORT = (data&0xf0)|(LCD_PORT&0x0f);
	
	_delay_ms(1);
	
	LCD_PORT&=~(1<<LCD_E);
	
	_delay_ms(1);
	
	LCD_PORT|=(1<<LCD_E);
	
	LCD_PORT = (data<<4)|(LCD_PORT&0x0f);
	
	_delay_ms(1);
	
	LCD_PORT&=~(1<<LCD_E);
	
	_delay_ms(1);
}

void lcdinit(void)
{
	LCD_DDR = 0xff;
	
	_delay_ms(45);
	
	lcd_write_instr(0x33);
	
	lcd_write_instr(0x32);
	
	lcd_write_instr(0x28);
	
	lcd_write_instr(0x08);
	
	lcd_write_instr(0x01);
	
	lcd_write_instr(0x06);
	
	lcd_write_instr(0x0f);
}

void lcd_clear(void)
{
	lcd_write_instr(1);
}

void lcd_set_xy(uint8_t x, uint8_t y)
{
	lcd_write_instr(0x80+x+y*0x40);
}


void lcd_write_text_xy(uint8_t x, uint8_t y, char *text)
{
	lcd_set_xy(x, y);
	
	while(*text)
	{
		lcd_write_data(*text);
		text++;
	}
}

int lcd_putc(char c, FILE *unused)
{
	lcd_write_data(c);
}

void blinking(uint8_t stan)
{
	if(stan == 0)
	{
		lcd_write_instr(0b1100);
	}
	else
	{
		lcd_write_instr(0b1111);
	}
	
}
