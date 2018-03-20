#ifndef __HBSENSOR_H__
#define __HBSENSOR_H__

#include "Arduino.h"

typedef enum {
    None,
    AnalogIn,
} SensorBusType;

class HbSensor
{
private:
    SensorBusType bus;
    int pin;
public:
    HbSensor();
    boolean attachBus(SensorBusType );
    boolean setPin(int );
    boolean init();
    int read();
};
#endif
