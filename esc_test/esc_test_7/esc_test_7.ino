// Added IMU inputs
// 
// Date: 21/11/2013
// Last Edited: 14:53 21/11/2013
// Author: Simon Anthony

#include <ADXL345.h>
#include <bma180.h>
#include <HMC58X3.h>
#include <ITG3200.h>
#include <MS561101BA.h>
#include <I2Cdev.h>
#include <MPU60X0.h>
#include <EEPROM.h>

#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>

int raw_values[9];
float ypr[3];
float val[9];

byte yJoy, xJoy; // store input data in these variables
int esc1 = 3, esc2 = 5, esc3 = 6, esc4 = 9; // ESC signal pins
int esc1y, esc1x, esc2y, esc2x, esc3y, esc3x, esc4y, esc4x; // ESC x and y values
int esc1Avg, esc2Avg, esc3Avg, esc4Avg; // ESC mixed axis values
int yAxis, xAxis; // x and y mapped values

int armTime; // ESC arm sequence counter
int freqCount=20; // input data counter
int pulseCount=0; // pulse length counter
int pulseDur = 1000; // ESC pulse duration (microseconds)

FreeIMU sensors = FreeIMU();

void setup() {
    pinMode(esc1, OUTPUT); // set output for ESC signals
    pinMode(esc2, OUTPUT);
    pinMode(esc3, OUTPUT);
    pinMode(esc4, OUTPUT);
    
    // init IMU
    Wire.begin();
    delay(5);
    sensors.init();
    delay(5);
   
    Serial.begin(19200); // start serial connection
    // arm_esc(); // run arming sequence for ESCs
    
    Serial.print("ESC & WiiChuck Demo.. ready!\n");
}

void loop() {
    if( freqCount >= 20 ) { // update input data every 20ms
        freqCount = 0; // reset loop counter

        sensors.getYawPitchRoll(ypr);
        
        yJoy = ypr[1];
        xJoy = ypr[2];
        
        if(yJoy > 128)
          yJoy = map(yJoy, 255, 128, 0, 128);
        
        if(xJoy > 128)
          xJoy = map(xJoy, 255, 128, 0, 128);
        
        Serial.print("Roll: "); Serial.print(yJoy, DEC);
        Serial.print("\t\tPitch: "); Serial.println(xJoy, DEC);
        
        // map input data range to ESC pulse range
        // yAxis = map(yJoy, 33, 227, 1000, 2000);
        // xAxis = map(xJoy, 26, 232, 1000, 2000);
        
        // lower and upper 20ms within the range defaults to lowest and highest speeds respectively
        // if(yAxis >= 1980)
        //   yAxis = 2000;
        // else if (yAxis <= 1020)
        //   yAxis = 1000;  
          
        // if(xAxis >= 1980)
        //   xAxis = 2000;
        // else if (xAxis <= 1020)
        //   xAxis = 1000;
        
        // yAxis = yAxis - 1500;
        // xAxis = xAxis - 1500;
        
        // Calculate ESC values for each axis  
        // esc1y = 1500 - yAxis;
        // esc1x = 1500 + xAxis;
        // esc1Avg = (esc1y + esc1x) / 2;
        
        // esc2y = 1500 - yAxis;
        // esc2x = 1500 - xAxis;
        // esc2Avg = (esc2y + esc2x) / 2;
        
        // esc3y = 1500 + yAxis;
        // esc3x = 1500 - xAxis;
        // esc3Avg = (esc3y + esc3x) / 2;
        
        // esc4y = 1500 + yAxis;
        // esc4x = 1500 + xAxis;
        // esc4Avg = (esc4y + esc4x) / 2;
          
        // pulse_esc(esc1, esc1Avg); // pulse ESC with input value
        // pulse_esc(esc2, esc2Avg);
        // pulse_esc(esc3, esc3Avg);
        // pulse_esc(esc4, esc4Avg);
            
        // Print data to serial monitor
        // Serial.print("yJoy: "); Serial.print((byte)yJoy,DEC);
        // Serial.print("\txJoy: "); Serial.println((byte)xJoy,DEC);
        
        
        
        /*
        Serial.println("##############################");
        
        Serial.print("ESC3 Y: "); Serial.print(esc3y,DEC);
        Serial.print("\tESC3 X: "); Serial.print(esc3x,DEC);
        Serial.print("\tESC3 Avg: "); Serial.println(esc3Avg,DEC);
        
        Serial.println("-----------------------------");
        
        Serial.print("ESC2 Y: "); Serial.print(esc2y,DEC);
        Serial.print("\tESC2 X: "); Serial.print(esc2x,DEC);
        Serial.print("\tESC2 Avg: "); Serial.println(esc2Avg,DEC);
        
        Serial.println("-----------------------------");
        
        Serial.print("ESC3 Y: "); Serial.print(esc3y,DEC);
        Serial.print("\tESC3 X: "); Serial.print(esc3x,DEC);
        Serial.print("\tESC3 Avg: "); Serial.println(esc3Avg,DEC);
        
        Serial.println("-----------------------------");
        
        Serial.print("ESC4 Y: "); Serial.print(esc4y,DEC);
        Serial.print("\tESC4 X: "); Serial.print(esc4x,DEC);
        Serial.print("\tESC4 Avg: "); Serial.println(esc4Avg,DEC);
        */
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
void pulse_esc(int escPin, int pulseLeng){
    digitalWrite(escPin, HIGH); // set pulse high
    delayMicroseconds(pulseLeng);
    digitalWrite(escPin, LOW); // set pulse high
}
