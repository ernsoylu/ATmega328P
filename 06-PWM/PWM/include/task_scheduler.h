#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <stdint.h>

extern volatile uint8_t flag_10ms;
extern volatile uint8_t flag_50ms;
extern volatile uint8_t flag_100ms;

void timer_scheduler_init(void);

#endif // TASK_SCHEDULER_H
