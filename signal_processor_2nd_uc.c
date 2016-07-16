#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "definition.h"
#include "lcd.h"

#define decVolume 1
#define incVolume 2
#define decSpeed 3
#define incSpeed 4
#define bass 5
#define treble 6

int vButton=0;
int sButton=0;

uint8_t xOrg[WS*2]; ///Signal from ADC
uint8_t button; //Button Pressed

ISR(INT0_vect)
{
	//received=PINC;
	//received=received>>4;
}

int main(void)
{
	init_port();
	init_interrupt();
	lcd_init();
	DDRA=0xff;
    while(1)
    {
		received=PINC;

		switch(PINC)
		{
			case decVolume:
			{
				vButton--;
				volume
				break;
			}
			case incVolume:
			{
				vButton++;
				break;
			}
			case decSpeed:
			{
				sButton--;				
				speed(vButton);
				break;
			}
			case incSpeed:
			{
				sButton++;
				speed(vButton);				
				break;
			}
			case bass:
			{
				
			}
			case treble:
			{
				
			}
			
			default:{}
			
		}
        
    } //while ends.
}