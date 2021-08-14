#include <Arduino.h>
#include <output.cpp>
#include <voltage.cpp>
#include <servoEx.cpp>
#include <range.cpp>

ServoEx s;

int pin = 10;
float maxSpeed = 600;

Range r1 = Range(1000, 1500, 2000);
Range r2 = Range(-90, 0, 90);
Range2 r = Range2(r1, r2);

void flashLed(int ms){
    digitalWrite(13, HIGH);
    delay(ms);
    digitalWrite(13, LOW);
}

void setup(){
    Serial.begin(9600);
    s = ServoEx(pin, maxSpeed, r);
    //pinMode(13, OUTPUT);
}

void loop(){
    Serial.println("loop start");

    s.setMoveAndRunTillDone(MOVE_TO_POS, 0);

    //flashLed(100);

    s.setMoveAndRunTillDone(MOVE_TO_POS, 180);

    //flashLed(100);

    s.setMoveAndRunTillDone(MOVE_TO_POS_WITH_TIME, 0, 2);

    //flashLed(100);

    s.setMoveAndRunTillDone(MOVE_TO_POS_AT_RATE, 180, 10);

    //flashLed(100);

    Serial.println("loop end");
}