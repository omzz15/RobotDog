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

    private:
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

    public:
        Voltage(unsigned short pin, float multiplier, unsigned int timeBetweenReadings, unsigned int measuresPerReading, unsigned int timeBetweenMeasures){
            this -> pin = pin;
            this -> multiplier = multiplier;
            this -> timeBetweenReadings = timeBetweenReadings;
            this -> measuresPerReading = measuresPerReading;
            this -> timeBetweenMeasures = timeBetweenMeasures;
        }

        Voltage(){
        }

        float getVoltage(){
            newVoltageAvalible = false;
            return voltage;
        }

        bool isNewVoltageAvalible(){
            return newVoltageAvalible;
        }

        void run(){
            if(millis() - lastReadingTime >= timeBetweenReadings)
                readVoltage();
        }
};