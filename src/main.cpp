#include <Arduino.h>
#include <output.cpp>
#include <voltage.cpp>
#include <servoEx.cpp>
#include <range.cpp>

ServoEx s;

int pin = 10;
float maxSpeed = 600;

Range r1 = Range(1000, 1500, 2000);
Range r2 = Range(0, 90, 180);
Range2 r = Range2(r1, r2);

void setup(){
    Serial.begin(9600);
    s = ServoEx(pin, maxSpeed, r);
    s.setServo(MOVE_TO_POS, 100);
}

void loop(){
    s.run();
    if(s.isDone())
        Serial.println("done");
    else{
        Serial.print("pos: ");
        Serial.println(s.getCurrentPos());
    }
}