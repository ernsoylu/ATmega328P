#include "uart.h"

void uart_init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // 8-bit data, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit_char(char data) {
    while (!(UCSR0A & (1 << UDRE0)));  // Wait for empty transmit buffer
    UDR0 = data;
}

void uart_print(const char* str) {
    while (*str) {
        uart_transmit_char(*str++);
    }
}

char uart_receive_char(void) {
    while (!(UCSR0A & (1 << RXC0)));  // Wait until data received
    return UDR0;
}

bool uart_data_available(void) {
    return (UCSR0A & (1 << RXC0));
}
