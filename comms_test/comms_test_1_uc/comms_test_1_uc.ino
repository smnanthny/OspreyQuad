// Comms Test 1 - User Controller
// 
// Date: 17/12/2013
// Last Edited: 15:26 17/12/2013
// Author: Simon Anthony

#include <SoftwareSerial.h>

SoftwareSerial comms(10,11); // Rx, Tx

byte START = 255, STOP = 128, count = 3, data = 70;
byte Rx;

void setup(){
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  Serial.println("User Controller [online]");
  
  comms.begin(19200);
}

void loop(){
  commSend();
}

void commSend(void){
  comms.write(START);
  Serial.println("Sent START");
  
  comms.write(count);
  Serial.print("Sent count: ");
  Serial.println(count);
  
  for(int i=0; i<count; i++){
    comms.write(data + i);
    Serial.print("Sent data: ");
    Serial.println(data + i);
  }
  
  comms.write(STOP);
  Serial.println("Sent STOP");
  
  while(comms.available() < 1){
    Serial.println("Waiting for ACK"); 
  }
  
  Rx = comms.read();
  if(Rx == 255){
    Serial.print("Received ACK: ");
    Serial.println(Rx);
  } else {
    Serial.println("ACK not received");
  }
  
  Serial.println("-----------------------");
  delay(10);
}
