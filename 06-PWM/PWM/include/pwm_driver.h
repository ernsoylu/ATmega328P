#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include <stdint.h>

typedef enum {
    TIMER1,
    TIMER2
} TimerID;

void timer_pwm_init(TimerID timer, char channel, uint16_t frequency_hz);
void timer_pwm_set_duty(TimerID timer, char channel, uint16_t duty);

#endif // PWM_DRIVER_H
