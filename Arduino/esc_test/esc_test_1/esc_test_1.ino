// Testing a single ESC spinning at a constant speed.
// 
// Date: 19/11/2013
// Last Edited: 19:10 19/11/2013
// Author: Simon Anthony

int Arming_Time=0;
int pin = 9;
// Enter value 1100us to Arm the ESC
// Enter value >= 1200us to run Motor to max 2000us
int Pulse = 1000;

// Arm the Servo within setup
void setup(){
 // initialise the digital pin as an output
 pinMode(pin, OUTPUT);
 // Will create a 1100us pulse to arm the ESC
 // The pulse will last for 20ms x 500 counts = 10,000ms or 10 seconds
 for (Arming_Time = 0; Arming_Time < 50; Arming_Time += 1){
  digitalWrite(pin, HIGH);
  delayMicroseconds(1100);
  digitalWrite(pin, LOW);
  delay(20 - (Pulse/1000));
 } 
}

void loop(){
  Pulse = 2000;
  
  digitalWrite(pin, HIGH);
  delayMicroseconds(Pulse);
  digitalWrite(pin, LOW);
  delay(18);
}
