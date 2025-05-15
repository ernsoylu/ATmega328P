#include <avr/io.h>
#include "task_scheduler.h"
#include "pwm_driver.h"
//Declare Variables
typedef struct{
    uint16_t duty;
} main_t;
// End of variable declaration
// Initialize global variables
main_t varmain = {0}; // Declare and initialize a global variable of type main_t
// End of global variable initialization

// Function prototypes
void task100ms(void){
  if(varmain.duty <UINT16_MAX){
    varmain.duty += 100; // Increment duty cycle by 1000
  } else {
    varmain.duty = 0; // Reset duty cycle to 0
  }
  timer_pwm_set_duty(TIMER1,'A', varmain.duty);
}
// End of function prototypes
int main(void) {
    //Initialization functions
    timer_scheduler_init();
    timer_pwm_init(TIMER1, 'A', 1000);     // 1 kHz on OC1A
    //End of initialization functions
    //Main loop
    while (1) {
        if (flag_100ms) {
            flag_100ms = 0;
            task100ms(); // Call the 100ms task
            // 100ms task
        }
    }
    // End of main loop
}

