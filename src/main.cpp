#include <Arduino.h>
#include <voltage.cpp>

Voltage v = Voltage(2,4,1000,10,3);

void setup(){
    v.setup();
    Serial.begin(9600);
}

void loop(){
    if(v.isVoltageExpired())
        Serial.println(v.getNewVoltage());
}