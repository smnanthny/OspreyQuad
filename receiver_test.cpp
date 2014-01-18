/*
    OspreyQuad Flight Controller
    ----------------------------
    Title: Receiver Testing
    Author: Simon Anthony
    Last Edited: 18/01/2014
*/

#include "mbed.h"

// ------------------------------------
// This class creates an input interrupt for a receiver channel and a corresponding timer.
// On a rising edge, the timer is reset and then starts counting.
// On a falling edge, the timer is stopped and the value is stored.
// Calling the .read() function returns the last stored value.
class Channel {
public:
    Channel(PinName pin) : channelInterrupt(pin)              // create InterruptIn on Channel pin
    {            
        channelInterrupt.rise(this, &Channel::startTimer);    // attach timer start to rising edge
        channelInterrupt.fall(this, &Channel::stopTimer);     // attach timer stop to falling edge
    }
    
    void startTimer(void)
    {
        channelTimer.reset();
        channelTimer.start();   
    }
    
    void stopTimer(void)
    {
        channelTimer.stop();
        period = channelTimer.read_us();
    }
    
    int readTimer(void)
    {
        return period;
    }
    
private:
    InterruptIn channelInterrupt;                             // Interrupt object
    Timer channelTimer;                                       // Timer object
    int period;                                               // Pulse period value
};

// ------------------------------------
// Create receiver input channels
Channel ch1(p11);
Channel ch2(p12);
Channel ch3(p13);
Channel ch4(p14);
Channel ch5(p15);
Channel ch6(p16);

// Create debug connection
Serial pc(USBTX, USBRX);

// ------------------------------------

int main()
{
    while(1)
    {
        wait(1);
        // Output channel values to debug connection
        pc.printf("Channel 1: %d\n", ch1.readTimer());
        pc.printf("Channel 2: %d\n", ch2.readTimer());
        pc.printf("Channel 3: %d\n", ch3.readTimer());
        pc.printf("Channel 4: %d\n", ch4.readTimer());
        pc.printf("Channel 5: %d\n", ch5.readTimer());
        pc.printf("Channel 6: %d\n\n", ch6.readTimer());
        pc.printf("---------------------------------------------\n\n");
    }
}