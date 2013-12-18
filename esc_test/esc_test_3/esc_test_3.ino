// Wii Nunchuck Z-button input controls the speed of all four ESCs simultaneously.
// 
// Date: 20/11/2013
// Last Edited: 17:40 20/11/2013
// Author: Simon Anthony

#include <Wire.h>
#include "nunchuck_funcs.h" // nunchuck input library

byte joyx,joyy,zbut,cbut; // store input data in these variables

int input_cnt=100; // input data counter
int esc_cnt=0; // ESC frequency counteri
int Arming_Time=0; // ESC arm sequence counter
int esc1 = 3, esc2 = 5, esc3 = 6, esc4 = 9; // ESC signal pins
int Pulse = 1000; // ESC pulse length (microseconds)

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
    if( input_cnt > 50 ) { // update input data every 50ms
        input_cnt = 0; // reset loop counter

        nunchuck_get_data(); // get data from nunchuck

        joyx  = nunchuck_joyx(); // ranges from approx 27 - 230
        joyy  = nunchuck_joyy(); // ranges from approx 33 - 227
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton();
        
        if(zbut) // check Z button state
          Pulse = 1500; // increase speed when Z button is high
        else
          Pulse = 1200; // reduce speed when Z button is low
            
        Serial.print("joyx: "); Serial.print((byte)joyx,DEC); // output input data to serial monitor
        Serial.print("\tjoyy: "); Serial.print((byte)joyy,DEC);
        Serial.print("\tzbut: "); Serial.print((byte)zbut,DEC);
        Serial.print("\tcbut: "); Serial.println((byte)cbut,DEC);
    }
    
    if(esc_cnt >= 20) { // run every 20ms
        esc_cnt = -1; // reset esc counter
        
        digitalWrite(esc1, HIGH); // set pulse high
        digitalWrite(esc2, HIGH);
        digitalWrite(esc3, HIGH);
        digitalWrite(esc4, HIGH);
        
        delayMicroseconds(Pulse); // delay by pulse length
        
        digitalWrite(esc1, LOW); // clear pulse low
        digitalWrite(esc2, LOW);
        digitalWrite(esc3, LOW);
        digitalWrite(esc4, LOW);
    }
    
    input_cnt++; // increment loop counter
    esc_cnt++; // increment esc counter
    delay(1); // delay by 1ms
}

// Arming the ESCs requires a 1ms pulse every 20ms. 
// The number of pulses required is vague between 10-50 pulses, so pulse 50 times for safety
void arm_esc(){
    for (Arming_Time = 0; Arming_Time < 50; Arming_Time++){ // pulse 50 times
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
