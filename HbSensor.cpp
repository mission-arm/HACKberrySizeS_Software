#include "Arduino.h"
#include "HbSensor.h"

HbSensor::HbSensor()
{
    this->bus = None;
    this->pin = -1;
};

boolean HbSensor::attachBus(SensorBusType bus)
{
    if ( bus == AnalogIn ) {
        this->bus = bus;
        return true;
    } else {
        return false;
    }
}

boolean HbSensor::setPin(int pin)
{
    if (this->bus != AnalogIn) return false;
    // TODO: pinが正しい範囲にあることを判定する
    this->pin = pin;
    return true;
}

boolean HbSensor::init()
{
    switch(this->bus)
    {
        case AnalogIn:
            return true;
        default:
            return false;
    }
}

int HbSensor::read()
{
    if ( this->bus == None ||
        (this->bus == AnalogIn && this->pin == -1) ) return -1;

    int i, sval;
    switch(bus)
    {
        case AnalogIn:
            for (i=0; i<10; i++) {
                sval += analogRead(this->pin);
            }
            sval = sval/10;
            return sval;
    }
}
