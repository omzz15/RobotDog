#include <Arduino.h>
#include <Servo.h>
#include <range.cpp>

enum ServoRunMode
{
    MOVE_TO_POS_AT_RATE,
    MOVE_TO_POS_WITH_TIME,
    MOVE_TO_POS
};

class ServoEx
{
    Servo servo;
    ServoRunMode runMode;
    Range2 ranges;

    float targetPos;
    float targetServoPos;
    float lastPos;

    long servoSetTime;
    long commandSetTime;

    float maxSpeed;
    float speed;

    private:
        float getRate(ServoRunMode runMode, float currentPos, float targetPos, float val = 0){
            float dis = getDistance(currentPos, targetPos);
            
            if(runMode == MOVE_TO_POS){
                val = maxSpeed;
            }
            else if(runMode == MOVE_TO_POS_WITH_TIME){
                return dis / val;
            }
            if(dis < 0)
                return -val;
            return val;
        }

        float getDistance(float currentPos, float targetPos){
            return targetPos - currentPos;
        }

    public:
        ServoEx(int pin, float maxSpeed, Range2 ranges){
            servo.attach(pin);
            this -> maxSpeed = maxSpeed;
            this -> ranges = ranges;
        }

        ServoEx(Servo servo, float maxSpeed, Range2 ranges){
            this -> servo = servo;
            this -> maxSpeed = maxSpeed;
            this -> ranges = ranges;
        }

        bool setCommand(ServoRunMode runMode, float position, float val = 0){
            
        }
}; //end of clas