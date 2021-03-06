/*
 * LFR.cpp
 *
 * Created: 11/10/2016 2:07:21 PM
 * Author : Manash
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL

#define BAUD 9600

#define MYUBRR F_CPU/16/BAUD - 1

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


void USART_Init(unsigned int ubrr)
{
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;
	
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << USBS) | (3 <<UCSZ0);
	
}

void USART_Transmit(unsigned char data){
	while (!(UCSRA & (1 << UDRE))) {};
	UDR = data;
}

bool USART_Transmit_String(char* command)
{
	bool ok = false;
	for (int i = 0; i < strlen(command); i++){
		USART_Transmit(command[i]);
		ok = true;
	}
	return ok;
}


static inline void initPWM(void){
	
	// Selecting PWM Mode [FastPWM - 8bit]
	TCCR1A |= (1 << WGM12) | (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	
	TCCR1B |= (1 << CS11) | (1 << CS10);
	
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << COM1B1);
	
	DDRB |= (1 << PB1);
	DDRB |= (1 << PB2);
}


/*
int main(void){
	USART_Init(MYUBRR);
	char command[] = "Hello World!\r\n";
	while(1){
		USART_Transmit_String(command);
		_delay_ms(1000);
	}
}
*/


/*
int main(void){
	initAllOut();
	while(true){
		blinkAll();
	}
}*/

int main(void){
	initPWM();
	
	while(true){
		for (int i = 0; i < 255; i++){
			OCR1B = i;
			_delay_ms(10);
		}
		_delay_ms(1000);
	}
}
