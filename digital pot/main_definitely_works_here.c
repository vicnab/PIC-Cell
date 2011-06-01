#include <p18cxxx.h>
#include <p18f4455.h>
#include <spi.h>
#include <stdio.h>
/* look in mcc18\doc\hlpPIC18ConfigSet.pdf */
# pragma config FOSC = INTOSC_EC //Internal oscillator, CLKOUT on RA6, EC used by USB
# pragma config WDT = OFF
# pragma config LVP = OFF
# pragma config BOR = ON
# pragma config PWRT = ON
# pragma config MCLRE = OFF
# pragma config CPUDIV = OSC1_PLL2
# pragma config PBADEN = OFF
#define OUT1 LATBbits.LATB0
#define PhoneOn PORTAbits.RA0
#define DTMF1 PORTAbits.RA1
#define DTMF2 PORTAbits.RA2
#define DTMF3 PORTAbits.RA3
#define DTMF4 PORTAbits.RA4
//#define POT_CS PORTBbits.RB7
//#define POT_CS_TRIS TRISBbits.TRISB7
#define POT_CS PORTBbits.RB7
#define POT_CK PORTBbits.RB6
#define POT_OUT PORTBbits.RB5
void nop(void);
void wait2(void);
void wait6(void);
void delay(void);

int spi_init(void);
int pot_init(void);

void spiout(unsigned char command, unsigned char byteout );
void spi_select(int dev);
void pot_off(void);
void pot_on(void);

void nop (void)
{
unsigned int i;
i++;
}
void delay()
{
	unsigned int i;
	for (i=0; i<10000; i++){
		};
}
void wait6()
{
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
}
void wait2()
{
	nop();
	nop();
}

void main (void)
{
	int SIG;
	int bogus; //do operations on this to delay
	unsigned char dummy;
	//SSPCON1 = 0x32; //00110010 WCOL = 0 (no collision
				   // SSPOV = 0, no overflow, SSPEN =1 SP enabled
					//CKP = 1 - idle state for clock is high level
					// bit 3-0 = 0010 = SPI master mode, clock = fosc/64
	ADCON1 = 0x0F; // sets AN4, AN3, AN2, AN1, AN0 to D I/O.
					// voltage reference bits to 0 (not AN2/AN3)
	OSCCON |= 0x70; //01110000 sets IRCF2:IRCF0 to 111 (internal clock 8 MHz)
	INTCON2 |= 0x80;
	UCON &= 0xF7; // clears bit 3
	CMCON = 0x07;
	CVRCON = 0x00;

	POT_CS = 0;
	POT_OUT = 0;
	POT_CK = 0;
	TRISB = 0x00;
	delay();
	delay();
	delay();
	delay();
	delay();
	POT_CS = 1;


	while (1){
	spiout(0xD3, 0xFF);
		

	}
}



/************************** SPI Init **************************************/
/* Initialises the PIC into SPI mode */

int spi_init(){

	//I Think we need to enable interrupts so that we know when we got a full byte from the SSP module

	INTCONbits.GIE = 1;						//Enable interrupts
	PIE1bits.SSPIE = 1;						//Enable interrupts for MSSP

	//SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_SS_DISABLED); //This may work but I know how to do it more clearly so I will!
	//setup the SPI

	SSPCON1 &= 0xF0;						//Keep top 7:4 bits same, SPI MASTER, FOSC/4
	SSPCON1bits.CKP = 0;					//Clock idle state is low
	SSPCON1bits.SSPEN = 1;					//Enable serial port and configure SCK, SDO, SDI, and SS as serial pins (not I/O pins anymore)
	SSPSTATbits.CKE = 1;					//Data valid on rising edge (because CKP = 0)
	SSPSTATbits.SMP = 0;					//Input data sampled at end of data output time ??? WHAT?!

	

	//Set up the ports correctly

	PORTC = 0x00; 							//Clear port C
	TRISC = 0x00;							//C0, C3, C5 are outputs, all else inputs C5:SDO,C3:SCK, C0:A2(mux) binary = 11010110

	//PORTA also
	PORTA = 0x00;							//Clear port A
	TRISA = 0x00;							//Outputs
	PORTD = 0x00;
	TRISD = 0x00;							//LED Outputs

	return 0;

}

	

void spiout(unsigned char command, unsigned char byteout )
{	
	int garbage;
	unsigned char bits,temp;
	POT_CS=0;

	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();
	
	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();
	
	POT_CK = 0;
	POT_OUT = 0;
	wait2();
	POT_CK = 1;
	wait2();

	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

		
	POT_CK = 0;
	POT_OUT = 0;
	wait2();
	POT_CK = 1;
	wait2();

		
	POT_CK = 0;
	POT_OUT = 0;
	wait2();
	POT_CK = 1;
	wait2();

	
	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

	
	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();
	//end command bit
	POT_CK = 0;
	POT_OUT = 11;
	wait2();
	POT_CK = 1;
	wait2();

	
	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

	
	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

	
	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();

	
	POT_CK = 0;
	POT_OUT = 1;
	wait2();
	POT_CK = 1;
	wait2();
	POT_CS = 1;

/*	for(bits=0;bits<8;bits++){
	  POT_OUT = (command & 0x1);    // select low bit;	
      POT_CK = 1;           // clock low
      command = command>>1;           // next bit
	  POT_CK = 0;
         // clock high
	}
	for(bits=0;bits<8;bits++){
	  POT_OUT = (byteout & 0x1);    // select low bit
	
      POT_CK = 1;               // clock low
      byteout = byteout>>1;           // next bit
	POT_CK = 0;
         // clock high
	}
	POT_CS=1;*/
}