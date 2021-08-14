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
    //the output servo class
    Servo servo;
    /*
    the ranges the servo uses to convert degrees to microseconds
    first range = microseconds
    second range = degrees
    */
    Range2 ranges;
    //the max speed of the servo
    float maxSpeed;
    //the target position of the servo
    float targetPos;
    //the last position of the servo
    float lastPos;
    //stores the current run mode
    ServoRunMode mode;
    //stores the time the command was set
    long commandSetTime;
    //stores the rate of the servo
    float rate;

private:
    float getRate(ServoRunMode servoRunMode, float targetPos, float currentPos, float val = 0)
    {
        if (servoRunMode == MOVE_TO_POS_AT_RATE)
        {
            if (targetPos > currentPos)
                return val;
            return -val;
        }
        else if (servoRunMode == MOVE_TO_POS_WITH_TIME)
        {
            return (targetPos - currentPos) / val;
        }
        else if (targetPos >= currentPos)
            return maxSpeed;
        return -maxSpeed;
    }

    float getServoMovement()
    {
        return ((micros() - commandSetTime) / 1000000.0) * rate;
    }

    void setServoDegs(float pos)
    {
        servo.writeMicroseconds(ranges.scale2To1(pos));
    }

    float getServoDegs()
    {
        return ranges.scale1To2(servo.readMicroseconds());
    }

public:
    ServoEx() {}

    ServoEx(int pin, float maxSpeed, Range2 ranges)
    {
        servo = Servo();
        servo.attach(pin);

        this->maxSpeed = maxSpeed;
        this->ranges = ranges;
    }

    ServoEx(Servo servo, float maxSpeed, Range2 ranges)
    {
        this->servo = servo;
        this->maxSpeed = maxSpeed;
        this->ranges = ranges;
    }

    void setMove(ServoRunMode mode, float pos, float val = 0)
    {
        rate = getRate(mode, pos, getCurrentPos(), val);

        if (abs(rate) <= maxSpeed)
        {
            this->mode = mode;
            this->targetPos = pos;
            this->lastPos = getCurrentPos();
            this->commandSetTime = micros();
        }
    }

    bool isDone()
    {
        return abs(getServoMovement()) > abs(targetPos - lastPos);
    }

    float getCurrentPos()
    {
        if (isDone())
            return targetPos;
        return lastPos + getServoMovement();
    }

    Servo getServo()
    {
        return servo;
    }

    Range2 getRanges()
    {
        return ranges;
    }

    float getMaxSpeed()
    {
        return maxSpeed;
    }

    float getTargetPos()
    {
        return targetPos;
    }

    ServoRunMode getMode()
    {
        return mode;
    }

    float getRate()
    {
        return rate;
    }

    float getTimeLeft()
    {
        return (targetPos - getCurrentPos()) / rate;
    }

    void run()
    {
        if (getServoDegs() != targetPos)
        {
            if (mode == MOVE_TO_POS)
                setServoDegs(targetPos);
            else
                setServoDegs(getCurrentPos());
        }
    }

    void runTillDone(){
        while(!isDone())
            run();
    }

    void setMoveAndRunTillDone(ServoRunMode mode, float pos, float val = 0){
        setMove(mode, pos, val);
        runTillDone();
    }
}; //end of class