#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"
# include <string.h>

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc, NULL, _FDEV_SETUP_WRITE);

char *litery[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

char *kody[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

char bufor[4];

int krotki = 500;
int dlugi = 1000;

int i = 0;
int miejsce_w_buforze = 0;
int miejsce_na_lcd = 0;


int main(void)
{
	DDRD = 0X00;
	DDRC=0XFF;
	
	PORTD=0XFF;
	
	lcdinit();
	blinking(0);
	
	PORTC = 0XFF;
	
	while(1)
	{
		if(!(PIND&(1<<1)))
		{
			while(!(PIND&(1<<1)))
			{
				i++;
				_delay_ms(1);
				
				PORTC=0X00;
			}
			
			PORTC=0XFF;
			
			if(i>10 && i<krotki)
			{
				bufor[miejsce_w_buforze] = '.';
				miejsce_w_buforze++;
				i=0;
			}
			else if(i>krotki && i<dlugi)
			{
				bufor[miejsce_w_buforze] = '-';
				miejsce_w_buforze++;
				i=0;
			}	
				
		}
		
		if (!(PIND&(1<<2)) || miejsce_w_buforze==4)
			{
				for(int j = 0; j<25; j++)
				{
					if(!strncmp(bufor, (char*)kody[j], 4))
					{
						lcd_set_xy(miejsce_na_lcd, 0);
						fprintf(&lcd_stream, "%c", *litery[j]);
						memset(bufor, 0, 4);
						miejsce_na_lcd++;
						miejsce_w_buforze=0;
						i=0;
						break;
						
					//	lcd_set_xy(miejsce_na_lcd, 0);
						//fprintf(&lcd_stream, "%4s", bufor);
						//memset(bufor, 0, 4);
					//	miejsce_w_buforze=0;
				//		
					}
					else
					{
					}
				}
				//lcd_set_xy(miejsce_na_lcd-1, 1);
				//fprintf(&lcd_stream, "0");
			}
		
		if(miejsce_na_lcd==17)
		{
			lcd_clear();
			miejsce_na_lcd=0;
		}
	
	}
	
	return 0;
}
