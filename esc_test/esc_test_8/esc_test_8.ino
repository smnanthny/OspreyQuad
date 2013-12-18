int currentMicros, lastMicros=0, interval;

void setup(){
  Serial.begin(115200);
}

void loop(){
  currentMicros = micros();
  interval = currentMicros - lastMicros;
  
  if(interval > 20000){
    Serial.print("Time since last pulse = ");
    Serial.println(interval);
    lastMicros = currentMicros;
  } else {
    Serial.println("Too soon...");
  }
}
