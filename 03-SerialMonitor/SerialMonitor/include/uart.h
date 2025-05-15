#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdbool.h>

// Initialize UART with the given UBRR value
void uart_init(unsigned int ubrr);

// Transmit one character
void uart_transmit_char(char data);

// Transmit a null-terminated string
void uart_print(const char* str);

// Receive one character (blocking)
char uart_receive_char(void);

// Check if data is available to read (non-blocking)
bool uart_data_available(void);

#endif
