#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
    // Set PB5 as output
    DDRB |= (1 << PB5);

    while (1)
    {
        // Toggle PB5
        PORTB ^= (1 << PB5);
        
        // Wait for 500 milliseconds
        _delay_ms(2000);
    }
}