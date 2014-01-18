/*
    OspreyQuad Project
    ~~~~~~~~~~~~~~~~~~~~~~~~
    Title: Flight Controller Test 1
    Author: Simon Anthony
    Created: 18/01/2014
*/

#include "mbed.h"

// ------------------------------------
// This class creates an input interrupt for a receiver channel and a corresponding timer.
// On a rising edge, the timer is reset and then starts counting.
// On a falling edge, the timer is stopped and the value is stored.
// Calling the .read() function returns the last stored value.
class Channel 
{
public:
    Channel(PinName pin) : channelInterrupt(pin)              // create InterruptIn on Channel pin
    {            
        channelInterrupt.rise(this, &Channel::startTimer);    // attach timer start to rising edge
        channelInterrupt.fall(this, &Channel::stopTimer);     // attach timer stop to falling edge
    }
    
    void startTimer(void)
    {
        pulseTimer.reset();                         // clear previous pulse timer
        pulseTimer.start();                         // start pulse timer        
    }
    
    void stopTimer(void)
    {
        pulseTimer.stop();                          // stop pulse timer
        pulseLength = pulseTimer.read_us();         // save pulse length
    }
    
    int readPulseTimer(void)
    {
        if(pulseLength > 2000)                      // housekeeping - pulse length limits [1000uS - 2000uS]
            pulseLength = 2000;
        else if(pulseLength < 1000)
            pulseLength = 1000;
            
        return pulseLength;                         // return pulse length
    }
    
    bool readConnTimer(void)
    {
        if((pulseLength > 1450) && (pulseLength < 1550))
            return true;
        else
            return false;
    }
    
private:
    InterruptIn channelInterrupt;                   // Interrupt object
    Timer pulseTimer;                               // Counts pulse length
    Timer connectionTimer;                          // Counts time between pulses
    int pulseLength;                                // Pulse length value
};

// ---------------------------------------------------

// Create receiver input channels
//Channel ch1(p11);       // Roll
Channel ch2(p12);       // Throttle
//Channel ch3(p13);       // Pitch
//Channel ch4(p14);       // Yaw
Channel ch5(p15);       // Left Switch
//Channel ch6(p16);       // Right Switch

// Define motor outputs
PwmOut motor1(p21);     // Motor 1
PwmOut motor2(p22);   // Motor 2
PwmOut motor3(p23);   // Motor 3
PwmOut motor4(p24);   // Motor 4

// PC serial port
Serial pc(USBTX, USBRX);

// ---------------------------------------------------

int main() 
{
    // flight controller mode
    // 0 = safe mode
    // 1 = flight mode
    // 2 = no radio mode
    int mode=0;
    
    // ESC pulse length
    int pulse;

    // Initialise motors
    motor1.period(0.020);
    motor2.period(0.020);
    motor3.period(0.020);
    motor4.period(0.020);
    
    wait(0.5);
    
    while(1) 
    {
        // set pulse length
        pulse = ch2.readPulseTimer();
        
        // read failsafe mode
        if(ch5.readPulseTimer() < 1800)
            mode = 1;                       // flight mode
        else
            mode = 0;                       // safe mode
            
        // check connection timeout on switch channel - cut power if timeout occurs
        if(ch5.readConnTimer())
            mode = 2;                       // no connection mode
        
        // output pulse value
        pc.printf("Throttle Input - %d\n", pulse);
        //pc.printf("Left Switch - %d\n\n", ch5.readPulseTimer());
    
        // check failsafe
        if(mode == 0)
        {
            // Update ECSs with 0% throttle
            motor1.pulsewidth(0.001);
            motor2.pulsewidth(0.001);
            motor3.pulsewidth(0.001);
            motor4.pulsewidth(0.001);
        } 
        else if(mode == 1)
        {
            // Update ECSs with controller input
            motor1.pulsewidth((float)pulse/1000000);
            motor2.pulsewidth((float)pulse/1000000);
            motor3.pulsewidth((float)pulse/1000000);
            motor4.pulsewidth((float)pulse/1000000);
        }
        else if(mode == 2)
        {
            // Disarm ESCs
            motor1.pulsewidth(0);
            motor2.pulsewidth(0);
            motor3.pulsewidth(0);
            motor4.pulsewidth(0);
        }
    }
}