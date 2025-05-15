#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1)

#define CMD_BUF_SIZE 16

int main(void) {
    uart_init(MYUBRR);

    // D13 (PB5) as output (LED)
    DDRB |= (1 << PB5);

    uart_print("System Ready. Type ON or OFF and press Enter:\r\n");

    char cmd_buf[CMD_BUF_SIZE];
    uint8_t buf_pos = 0;

    while (1) {
        // Check for serial input
        if (uart_data_available()) {
          char c = uart_receive_char();
      
          // Accept only printable ASCII characters and control chars
          if ((c >= 32 && c <= 126) || c == '\r' || c == '\n') {
              uart_transmit_char(c); // Echo
      
              if (c == '\r' || c == '\n') {
                  cmd_buf[buf_pos] = '\0';
      
                  if (strcmp(cmd_buf, "ON") == 0) {
                      PORTB |= (1 << PB5);
                      uart_print("\r\nLED ON\r\n");
                  } else if (strcmp(cmd_buf, "OFF") == 0) {
                      PORTB &= ~(1 << PB5);
                      uart_print("\r\nLED OFF\r\n");
                  } else {
                      uart_print("\r\nUnknown command\r\n");
                  }
      
                  buf_pos = 0;
              } else if (buf_pos < CMD_BUF_SIZE - 1) {
                  cmd_buf[buf_pos++] = c;
              }
          }
      }
      
    }

    return 0;
}
