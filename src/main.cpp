#include <Arduino.h>
#include <output.cpp>
#include <voltage.cpp>
#include <servoEx.cpp>
#include <range.cpp>

int lPin = 13;
int lTime = 100;

void initLed(int pin = lPin){
    pinMode(pin, OUTPUT);
}

void flashLed(int ms = lTime, int pin = lPin, bool delayAfter = true){
    digitalWrite(pin, HIGH);
    delay(ms);
    digitalWrite(pin, LOW);
    if(delayAfter)
        delay(ms);
}

void setup(){
    initLed();
}

void loop(){
    flashLed();
}