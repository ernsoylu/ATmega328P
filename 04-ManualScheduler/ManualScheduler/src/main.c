#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdint.h>

volatile uint16_t tick_count = 0;
volatile uint8_t flag_10ms = 0;
volatile uint8_t flag_50ms = 0;
volatile uint8_t flag_100ms = 0;

void timer_scheduler_init(void){
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

void task_10ms(void) {
    // Task to be executed every 10ms
    PIND |= (1 << PD2); // Toggle LED on PD2
}
void task_50ms(void) {
    // Task to be executed every 50ms
    PIND |= (1 << PD3); // Toggle LED on PD3
}
void task_100ms(void) {
    // Task to be executed every 100ms
    PIND |= (1 << PD4); // Toggle LED on PD4
}

int main(void) {
    // Set PD2, PD3, PD4 as output
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4);
    
    // Initialize Timer1
    timer_scheduler_init();
    
    // Enable global interrupts
    sei();
    
    while (1) {
        if (flag_10ms) {
            flag_10ms = 0;
            task_10ms();
        }
        if (flag_50ms) {
            flag_50ms = 0;
            task_50ms();
        }
        if (flag_100ms) {
            flag_100ms = 0;
            task_100ms();
        }
    }
}
