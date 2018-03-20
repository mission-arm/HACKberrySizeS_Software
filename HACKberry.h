#ifndef __HACKBERRY_H__
#define __HACKBERRY_H__

#include "Arduino.h"
#include <Servo.h>

#include "HbButton.h"
#include "HbSensor.h"

typedef enum {
    NONE,
    Mk1Right,
    Mk1Left,
    Mk2Right,
    Mk2Left,
    SizeSRight,
    SizeSLeft
} BoardType;

class HACKberry {
public:

// member values
    // Objects
    BoardType board;
    HbButton  ButtonCalib;
    HbButton  ButtonExtra;
    HbButton  ButtonThumb;
    HbButton  ButtonOther;
    HbSensor  Sensor;
    Servo     ServoIndex;
    Servo     ServoOther;
    Servo     ServoThumb;

    // Status
    // TBI: init them in init();
    boolean isThumbOpen=false;
    boolean isOtherLock=false;
    int SensorValue;
    int angle_position;
    int angle_speed;
    int preangle_position;
    int TargetAngleThumb;
    int TargetAngleIndex;
    int TargetAngleOther;

    // constatnt
    const int NormalizedAngleMaxPosition = 100;
    const int NormalizedAngleMinPosition = 0;
    const int NormalizedSensorMax = 100;
    const int NormalizedSensorMin = 0;

    // Parameters for Sensor
    int MinSensorRangeStop; // Minimum Value of Range for finger not moving
    int MaxSensorRangeStop;
    int MinSensorValue;
    int MaxSensorValue;

    // Parameters for Servo Control
    // MinReverseSpeed < MaxReverseSpeed < MinForwardSpeed < MaxForwardSpeed
    int MaxForwardSpeed;
    int MinForwardSpeed;
    int MaxReverseSpeed;
    int MinReverseSpeed;

    int AngleThumbMin;
    int AngleThumbMax;
    int AngleIndexMin;
    int AngleIndexMax;
    int AngleOtherMin;
    int AngleOtherMax;

    int AngleThumbOpen;
    int AngleThumbClose;
    int AngleIndexOpen;
    int AngleIndexClose;
    int AngleOtherOpen;
    int AngleOtherClose;

    // Callback functions for switch
    // Not In Use
    void (*CalibCB)();
    void (*ExtraCB)();
    void (*ThumbCB)();
    void (*OtherCB)();

// functions
    HACKberry();
    HACKberry(BoardType);

    void setBoardType(BoardType);
    void setAngleIndex(int , int );
    void setAngleOther(int , int );
    void setAngleThumb(int , int );
    void setSpeedRange(int , int , int , int );
    void setSensorThreshold(int , int );

    // Not In Use
    void setCalibCallBack(void (*)(void*));
    void setExtraCallBack(void (*)(void*));
    void setThumbCallBack(void (*)(void*));
    void setOtherCallBack(void (*)(void*));

    void init();
    void readSensor();
    void calcPosition();
    void controlServo();
    void calibration(unsigned long);

};
#endif
