#include<Arduino.h>

class Voltage{

    float voltage;
    bool newVoltageAvalible;

    unsigned short pin;
    float multiplier;
    unsigned int timeBetweenReadings;
    unsigned int measuresPerReading;
    unsigned int timeBetweenMeasures;

    unsigned long lastReadingTime = 0;

    public:
        Voltage(unsigned short pin, float multiplier, unsigned int timeBetweenReadings, unsigned int measuresPerReading, unsigned int timeBetweenMeasures){
            this -> pin = pin;
            this -> multiplier = multiplier;
            this -> timeBetweenReadings = timeBetweenReadings;
            this -> measuresPerReading = measuresPerReading;
            this -> timeBetweenMeasures = timeBetweenMeasures;
        }

        Voltage(){}

        void setup(){
            pinMode(pin, INPUT);
        }

        void readVoltage(){
            float temp = 0;
            for(unsigned int i = 0; i < measuresPerReading; i++){
                temp += (analogRead(pin) * 5 * multiplier) / 1024.0;
                delay(timeBetweenMeasures);
            }
            voltage = temp / measuresPerReading;
            newVoltageAvalible = true;
            lastReadingTime = millis(); 
        }

        float getVoltage(){
            newVoltageAvalible = false;
            return voltage;
        }

        float getNewVoltage(){
            readVoltage();
            return getVoltage();
        }

        bool isNewVoltageAvalible(){
            return newVoltageAvalible;
        }
        
        bool isVoltageExpired(){
            return millis() - lastReadingTime >= timeBetweenReadings;
        }

        void run(){
            if(isVoltageExpired())
                readVoltage();
        }

        
};