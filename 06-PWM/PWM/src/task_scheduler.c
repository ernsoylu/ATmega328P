#include <avr/io.h>
#include <avr/interrupt.h>
#include "task_scheduler.h"

volatile uint8_t flag_10ms = 0;
volatile uint8_t flag_50ms = 0;
volatile uint8_t flag_100ms = 0;

void timer_scheduler_init(void) {
    TCCR0A = (1 << WGM01);              // CTC Mode
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler = 64
    OCR0A = 249;                        // 1ms tick @ 16MHz
    TIMSK0 = (1 << OCIE0A);             // Enable Compare Match A Interrupt
    sei();                              // Enable global interrupts
}

ISR(TIMER0_COMPA_vect) {
    static uint8_t cnt10 = 0, cnt50 = 0, cnt100 = 0;
    if (++cnt10 >= 10) { cnt10 = 0; flag_10ms = 1; }
    if (++cnt50 >= 50) { cnt50 = 0; flag_50ms = 1; }
    if (++cnt100 >= 100) { cnt100 = 0; flag_100ms = 1; }
}
