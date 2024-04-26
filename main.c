#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD_RATE 9600

// Función para inicializar UARTvoid UART_Init() {
UBRR0H = (uint8_t)(F_CPU/(BAUD_RATE*16UL)-1)>>8; // Establecer velocidad en baudios
UBRR0L = (uint8_t)(F_CPU/(BAUD_RATE*16UL)-1);
UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Habilitar receptor y transmisor
UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); // Establecer formato de trama: 8 bits de datos, 1 bit de parada, sin paridad
}
// Función para transmitir un carácter vía UART
void UART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer
	UDR0 = data; // Coloca los datos en el buffer, envía los datos.
}


unsigned char UART_Receive() {
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

int main(void) {
	UART_Init();
	
	while (1) {
		UART_Transmit('\n');
		UART_Transmit('1');
		UART_Transmit('.');
		UART_Transmit(' ');
		UART_Transmit('L');
		UART_Transmit('e');
		UART_Transmit('e');
		UART_Transmit('r');
		UART_Transmit(' ');
		UART_Transmit('p');
		UART_Transmit('o');
		UART_Transmit('t');
		UART_Transmit('e');
		UART_Transmit('n');
		UART_Transmit('c');
		UART_Transmit('i');
		UART_Transmit('o');
		UART_Transmit('m');
		UART_Transmit('e');
		UART_Transmit('t');
		UART_Transmit('r');
		UART_Transmit('o');
		UART_Transmit('\n');
		
		UART_Transmit('2');
		UART_Transmit('.');
		UART_Transmit(' ');
		UART_Transmit('E');
		UART_Transmit('n');
		UART_Transmit('v');
		UART_Transmit('i');
		UART_Transmit('a');
		UART_Transmit('r');
		UART_Transmit(' ');
		UART_Transmit('A');
		UART_Transmit('s');
		UART_Transmit('c');
		UART_Transmit('i');
		UART_Transmit('i');
		UART_Transmit('\n');


		unsigned char option;
		do {
			option = UART_Receive();
		} while (option != '1' && option != '2');

		
		if (option == '1') {
			//Lee el valor del potenciómetro
			// Suponiendo que el potenciómetro esté conectado a ADC0 (pin A0)
			ADMUX = (1 << REFS0);
			ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
			ADCSRA |= (1 << ADSC);
			while (ADCSRA & (1 << ADSC));
			uint16_t potValue = ADC;
			UART_Transmit('\n');
			UART_Transmit('P');
			UART_Transmit('o');
			UART_Transmit('t');
			UART_Transmit('e');
			UART_Transmit('n');
			UART_Transmit('c');
			UART_Transmit('i');
			UART_Transmit('o');
			UART_Transmit('m');
			UART_Transmit('e');
			UART_Transmit('t');
			UART_Transmit('r');
			UART_Transmit('o');
			UART_Transmit(' ');
			UART_Transmit('V');
			UART_Transmit('a');
			UART_Transmit('l');
			UART_Transmit('o');
			UART_Transmit('r');
			UART_Transmit(':');
			UART_Transmit(' ');
			UART_Transmit((potValue / 1000) % 10 + '0'); // Transmit thousands digit
			UART_Transmit((potValue / 100) % 10 + '0'); // Transmit hundreds digit
			UART_Transmit((potValue / 10) % 10 + '0');  // Transmit tens digit
			UART_Transmit((potValue % 10) + '0');       // Transmit ones digit
			UART_Transmit('\n');
			} else if (option == '2') {
			// Send ASCII character
			UART_Transmit('\n');
			UART_Transmit('E');
			UART_Transmit('n');
			UART_Transmit('v');
			UART_Transmit('i');
			UART_Transmit('a');
			UART_Transmit('r');
			UART_Transmit(' ');
			UART_Transmit('A');
			UART_Transmit('s');
			UART_Transmit('c');
			UART_Transmit('i');
			UART_Transmit('i');
			UART_Transmit(':');
			UART_Transmit(' ');

		}
	}
}

