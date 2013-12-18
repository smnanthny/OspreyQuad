// Comms Test 1 - Flight Controller
// 
// Date: 17/12/2013
// Last Edited: 15:26 17/12/2013
// Author: Simon Anthony

#include <SoftwareSerial.h>

SoftwareSerial comms(10,11); // Rx, Tx

byte count, data[8];
byte received;

int timer;

void setup(){
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  Serial.println("Flight Controller [online]");
  
  comms.begin(19200);
}

void loop(){
  if(comms.available() > 0){
  
    received = comms.read();
    if(received == 255){
      Serial.println("START received");
      
      count = comms.read();
      Serial.print("Count received: ");
      Serial.println(count);
      
      if(count < 10){
        for(int i=0; i<count; i++){
          data[i] = comms.read();
          Serial.print("Data byte received: ");
          Serial.println(data[i]);
        }
      }
      
      received = comms.read();
      if(received == 128){
        Serial.println("STOP received");
        comms.write(255);
        Serial.println("ACK sent");
      } else {
        Serial.println("STOP not received..");
      }
        
    } else {
      Serial.println("######## No START received #######");
    }
    
  } else {
    Serial.println("########## No data ready ###########");
    timer++;
    
    if(timer > 100){
      comms.write(255);
      Serial.println("~~~~~~~~~ Reset sent");
      timer = 0;
    }
  }
  
  Serial.println("-------------------");
}
