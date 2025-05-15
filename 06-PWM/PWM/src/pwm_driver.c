#include "pwm_driver.h"
#include <avr/io.h>

#define F_CPU 16000000UL

void timer_pwm_init(TimerID timer, char channel, uint16_t frequency_hz) {
    switch (timer) {
        case TIMER1: {
            uint16_t top_value = (F_CPU / (8UL * frequency_hz)) - 1;
            if (channel == 'A') {
                DDRB |= (1 << PB1);
                TCCR1A |= (1 << COM1A1) | (1 << WGM11);
            } else if (channel == 'B') {
                DDRB |= (1 << PB2);
                TCCR1A |= (1 << COM1B1) | (1 << WGM11);
            }
            TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);
            ICR1 = top_value;
            break;
        }

        case TIMER2: {
            if (channel == 'A') {
                DDRB |= (1 << PB3);
                TCCR2A |= (1 << COM2A1) | (1 << WGM20) | (1 << WGM21);
            } else if (channel == 'B') {
                DDRD |= (1 << PD3);
                TCCR2A |= (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
            }
            TCCR2B |= (1 << CS22);
            break;
        }
    }
}

void timer_pwm_set_duty(TimerID timer, char channel, uint16_t duty) {
    switch (timer) {
        case TIMER1: {
            uint16_t top = ICR1;
            uint16_t value = ((uint32_t)duty * top) / 65535;
            if (channel == 'A') OCR1A = value;
            else if (channel == 'B') OCR1B = value;
            break;
        }
        case TIMER2: {
            uint8_t value = ((uint32_t)duty * 255) / 65535;
            if (channel == 'A') OCR2A = value;
            else if (channel == 'B') OCR2B = value;
            break;
        }
    }
}
