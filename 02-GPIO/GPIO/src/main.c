#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set PD2 (D2) as input
    DDRD &= ~(1 << PD2);

    // Enable internal pull-up resistor on PD2
    PORTD |= (1 << PD2);

    // Set PB5 (D13) as output
    DDRB |= (1 << PB5);

    while (1) {
        // Read the pin
        if ((PIND & (1 << PD2)) == 0) {
            // Switch pressed → input LOW
            PORTB |= (1 << PB5);  // Turn ON LED
        } else {
            // Switch not pressed → input HIGH
            PORTB &= ~(1 << PB5); // Turn OFF LED
        }

        _delay_ms(10);
    }

    return 0;
}
