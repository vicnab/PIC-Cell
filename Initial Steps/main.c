#include <p18cxxx.h>
#include<p18f4455.h>
/* look in mcc18\doc\hlpPIC18ConfigSet.pdf */
# pragma config FOSC = INTOSC_EC //Internal oscillator, CLKOUT on RA6, EC used by USB
# pragma config WDT = OFF
# pragma config LVP = OFF
# pragma config MCLRE = OFF
# pragma config CPUDIV = OSC1_PLL2
# pragma config PBADEN = OFF
#define OUT1 LATBbits.LATB0
#define PhoneOn PORTAbits.RA0
#define DTMF1 PORTAbits.RA1
#define DTMF2 PORTAbits.RA2
#define DTMF3 PORTAbits.RA3
#define DTMF4 PORTAbits.RA4

void delay (void)
{
	unsigned int i;
	for (i=0; i<10000; i++){
		};
}

void main (void)
{
	int SIG;
	ADCON1 = 0x0F; // sets AN4, AN3, AN2, AN1, AN0 to D I/O.
					// voltage reference bits to 0 (not AN2/AN3)
	OSCCON |= 0x70; //01110000 sets IRCF2:IRCF0 to 111 (internal clock 8 MHz)
	INTCON2 |= 0x80;
	UCON &= 0xF7; // clears bit 3
	CMCON = 0x07;
	CVRCON = 0x00; 
	PORTB = 0x00;
	TRISB =0x00;
	TRISA =0xFF;
	
	OUT1=0;
	PORTB = 0x00;
	while (1){
	PORTB= 0x08;// turn on RB3 only 
			delay();
			delay();
	if(PhoneOn){
		if(DTMF1 == 1 && DTMF2 ==0 && DTMF3 == 0 && DTMF4 ==0){ 
			PORTB= 0x80; // turn on RB7 only
			delay();
			delay();
			}
		else if(DTMF1 == 0 && DTMF2 ==1 && DTMF3 == 0 && DTMF4 ==0){ 
			 PORTB= 0x40; // turn on RB6 only  
			delay();
			delay();
			}
		else if(DTMF1 == 1 && DTMF2 ==1 && DTMF3 == 0 && DTMF4 ==0){ 
			 PORTB= 0x20; // turn on RB5 only 
			delay();
			delay();
			}
		else if(DTMF1 == 0 && DTMF2 ==0 && DTMF3 == 1 && DTMF4 ==0){ 
			PORTB= 0x10;  // turn on RB4 only
			delay();
			delay();
			}
		else if(DTMF1 == 1 && DTMF2 ==0 && DTMF3 == 1 && DTMF4 ==0){ 
			PORTB= 0x08;// turn on RB3 only 
			delay();
			delay();
			}
		else if(DTMF1 == 0 && DTMF2 ==1 && DTMF3 == 1 && DTMF4 ==0){ 
			PORTB= 0x04; // turn on RB2 only 
			delay();
			delay();
			}
		else if(DTMF1 == 1 && DTMF2 ==1 && DTMF3 == 1 && DTMF4 ==0){ 
			PORTB= 0x02; //turn on RB1 only
			delay();
			delay();
			}
		else if(DTMF1 == 0 & DTMF2 ==0 & DTMF3 == 0 & DTMF4 ==1){ 
			PORTB= 0x01; // turn on RB0 only 
			delay();
			delay();
			}
		else
			PORTB = 0x00;
	}
	else
		{ 	PORTB= 0x08;// turn on RB3 only 
			delay();
			delay();
		}
}
}
	

	


	