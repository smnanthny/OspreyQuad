// Testing all 4 ESCs simultaneously at the same speed
// 
// Date: 19/11/2013
// Last Edited: 21:10 19/11/2013
// Author: Simon Anthony

int Arming_Time=0;
int esc1 = 3, esc2 = 5, esc3 = 6, esc4 = 9;
// Enter value 1100us to Arm the ESC
// Enter value >= 1200us to run Motor to max 2000us
int Pulse = 1000;

// Arm the Servo within setup
void setup(){
 pinMode(esc1, OUTPUT);
 pinMode(esc2, OUTPUT);
 pinMode(esc3, OUTPUT);
 pinMode(esc4, OUTPUT);
 
 for (Arming_Time = 0; Arming_Time < 500; Arming_Time += 1){
  digitalWrite(esc1, HIGH);
  digitalWrite(esc2, HIGH);
  digitalWrite(esc3, HIGH);
  digitalWrite(esc4, HIGH);
  delayMicroseconds(1100);
  digitalWrite(esc1, LOW);
  digitalWrite(esc2, LOW);
  digitalWrite(esc3, LOW);
  digitalWrite(esc4, LOW);
  delay(20 - (Pulse/1000));
 } 
}

void loop(){
  Pulse = 1300;
  
  digitalWrite(esc1, HIGH);
  digitalWrite(esc2, HIGH);
  digitalWrite(esc3, HIGH);
  digitalWrite(esc4, HIGH);
  delayMicroseconds(Pulse);
  digitalWrite(esc1, LOW);
  digitalWrite(esc2, LOW);
  digitalWrite(esc3, LOW);
  digitalWrite(esc4, LOW);
  delay(20 - (Pulse/1000));
}
