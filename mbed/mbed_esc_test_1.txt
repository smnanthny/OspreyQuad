/*
    OspreyQuad Project
    ~~~~~~~~~~~~~~~~~~~~~~~~
    Title: mbed_esc_test_1
    Author: Simon Anthony
    Created: 21/12/2013
*/

#include "mbed.h"

PwmOut motor(p21);
Serial pc(USBTX, USBRX);

int main() {

    float pulse = 0.001;

    motor.period(0.020); //50 Hz - 20ms period
    motor.pulsewidth(pulse); // initialise ESC
    
    wait(1);
    
    pc.printf("Press 'u' to increment the speed by 10uS or 'd' to decrement by 10uS.\n");
    
    pulse = 0.0012;
    pc.printf("Current speed: %.0f%%\n", (pulse-0.001)*100000);
    
    while(1){
    
        if(pc.readable()){
            char c = pc.getc();
            
            if((c == 'u') && (pulse < 0.00199)){
                pulse += 0.00001;
                pc.printf("Current speed: %.0f%%\n", (pulse-0.001)*100000);
            }
            
            if((c == 'd') && (pulse > 0.00121)){
                pulse -= 0.00001;
                pc.printf("Current speed: %.0f%%\n", (pulse-0.001)*100000);
            }
        }
    
        motor.pulsewidth(pulse);
    
    }
}