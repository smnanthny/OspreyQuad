/**
 * Streams calibrated sensors readings.
 *
 * @author Fabio Varesano - fvaresano at yahoo dot it
*/ 

/*
Development of this code has been supported by the Department of Computer Science,
Universita' degli Studi di Torino, Italy within the Piemonte Project
http://www.piemonte.di.unito.it/


This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ADXL345.h>
#include <bma180.h>
#include <HMC58X3.h>
#include <ITG3200.h>
#include <MS561101BA.h>
#include <I2Cdev.h>
#include <MPU60X0.h>
#include <EEPROM.h>

//#define DEBUG
#include "DebugUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>


float val[11];
unsigned long newMicros, lastMicros, interval=0;


// Set the default object
FreeIMU my3IMU = FreeIMU();

void setup() { 
  Serial.begin(57600);
  Wire.begin();
  
  delay(500);
  my3IMU.init(true); // the parameter enable or disable fast mode
  delay(500);
}

void loop() {
  newMicros = micros();
  my3IMU.getValues(val);
  interval = newMicros - lastMicros;
  lastMicros = newMicros;
  
    Serial.print(interval);
    Serial.print(",");
    Serial.print(val[0], 2);
    Serial.print(",");
    Serial.print(val[1], 2);
    Serial.print(",");
    Serial.print(val[2], 2);
    Serial.print(",");
    Serial.print(val[3], 2);
    Serial.print(",");
    Serial.print(val[4], 2);
    Serial.println("");
}

