// Title: Battery Monitor
// Date: 02/12/2013
// Last Edited: 22:43 02/12/2013
// Author: Simon Anthony
//
// NOTES:
// 3.4V = 173.5, so use less than 174
//          __________
// N/C    --|        |-- Vcc
// Cell 3 --|        |-- Cell 1
// Cell 2 --|        |-- Tx
// GND    --|        |-- Rx
//          ----------

#include <SoftwareSerial.h>
//SoftwareSerial fcComms(0, 1); // Rx, Tx

byte c1, c2, c3;
int LED = 0;

void setup(){
  //fcComms.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop(){
  c1 = analogRead(1);
  c2 = analogRead(2);
  c3 = analogRead(3);
    
  if(c1 < 174){
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
    
  if(c2 < 174){
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
    
  if(c3 < 174){
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
}

/*
// mapfloat() maps float variables similar to map()
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
*/
