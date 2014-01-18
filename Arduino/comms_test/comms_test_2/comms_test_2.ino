/*
  Osprey Quadcopter Project
  Author: Simon Anthony
  Created: 17th December 2013
  Title: Comms Test 2
*/

#include <Osprey.h>
#include <SoftwareSerial.h>

Osprey quad;

int count = 3;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  quad.commsTransmit(5);
}
