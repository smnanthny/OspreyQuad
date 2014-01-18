// Reworked standby mode.
// 
// Date: 21/11/2013
// Last Edited: 14:53 21/11/2013
// Author: Simon Anthony

#include <Wire.h> // i2c library
#include "nunchuck_funcs.h" // nunchuck input library

byte xJoy,zBtn; // store input data in these variables
int esc1 = 3, esc2 = 5, esc3 = 6, esc4 = 9; // ESC signal pins

int armTime; // ESC arm sequence counter
int freqCount=20; // input data counter
int pulseDur = 1000; // ESC pulse duration (microseconds)
int flagStandby = 0; // standby mode flag

void setup() {
    pinMode(esc1, OUTPUT); // set output for ESC signals
    pinMode(esc2, OUTPUT);
    pinMode(esc3, OUTPUT);
    pinMode(esc4, OUTPUT);
   
    Serial.begin(19200); // start serial connection
    nunchuck_setpowerpins(); // set nunchuck + and - pins
    nunchuck_init(); // send the initilization handshake
    arm_esc(); // run arming sequence for ESCs
    
    Serial.print("ESC & WiiChuck Demo.. ready!\n");
}

void loop() {
    if( freqCount >= 20 ) { // update input data every 20ms
        freqCount = 0; // reset loop counter

        nunchuck_get_data(); // get data from nunchuck

        zBtn = nunchuck_zbutton(); // save Z button state
        xJoy = nunchuck_joyx(); // ranges from approx 27 - 230
        
        // pressing Z button alternates standby mode
        if(zBtn){
          if(flagStandby == 0){
            flagStandby = 1; // enter standby mode
            pulseDur = 1000; // set pulse speed to minimum setting
          } else if(flagStandby == 1)
            flagStandby = 0; // exit standby mode
        }
        
        // check standby flag
        if(flagStandby == 1){
            pulse_esc(); // pulse ESCs while in standby with previously set 1ms
        } else {
            // map input data range to ESC pulse range
            pulseDur = map(xJoy, 26, 232, 1000, 2000);
            
            // lower and upper 20ms within the range defaults to lowest and highest speeds respectively
            if(pulseDur >= 1980)
              pulseDur = 2000;
            else if (pulseDur <= 1020)
              pulseDur = 1000;  
              
            pulse_esc(); // pulse ESC with input value
        }
            
        // Print data to serial monitor
        Serial.print("xJoy: "); Serial.print((byte)xJoy,DEC);
        Serial.print("\tpulseDur: "); Serial.print(pulseDur,DEC);
        Serial.print("\tzButton: "); Serial.println((byte)zBtn,DEC);
        Serial.print("\tstandby: "); Serial.println((byte)zBtn,DEC);
    }
    
    freqCount++; // increment loop counter
    delay(1); // delay by 1ms
}

// Arming the ESCs requires a 1ms pulse every 20ms. 
// The number of pulses required is vague between 10-50 pulses, so pulse 50 times for safety
void arm_esc(){
    for (armTime = 0; armTime < 50; armTime++){ // pulse 50 times
     digitalWrite(esc1, HIGH); // set pulse high
     digitalWrite(esc2, HIGH);
     digitalWrite(esc3, HIGH);
     digitalWrite(esc4, HIGH);
     
     delay(1); // 1ms pulse delay
     
     digitalWrite(esc1, LOW); // clear pulse low
     digitalWrite(esc2, LOW);
     digitalWrite(esc3, LOW);
     digitalWrite(esc4, LOW);
     
     delay(20); // 20ms between each pulse
    }     
}

// update the ESCs
void pulse_esc(){
    digitalWrite(esc1, HIGH); // set pulse high
    digitalWrite(esc2, HIGH);
    digitalWrite(esc3, HIGH);
    digitalWrite(esc4, HIGH);
    
    delayMicroseconds(pulseDur); // delay by pulse length
    
    digitalWrite(esc1, LOW); // clear pulse low
    digitalWrite(esc2, LOW);
    digitalWrite(esc3, LOW);
    digitalWrite(esc4, LOW);
}
