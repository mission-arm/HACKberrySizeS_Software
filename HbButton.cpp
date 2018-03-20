#include "Arduino.h"
#include "HbButton.h"

HbButton::HbButton() {
}

HbButton::HbButton(int pin, boolean isDigital, boolean isPullup)
{
    this->pin = pin;
    this->isDigital = isDigital;
    this->isPullup = isPullup;

    if (isDigital) {
        if (isPullup) {
            pinMode(pin, INPUT_PULLUP);
        } else {
            pinMode(pin, INPUT);
        }
    } else {
    }
}

HbButton::HbButton(int pin)
{
    this->pin = pin;
    this->isDigital = true;
    this->isPullup = true;

    if (isDigital) {
        if (isPullup) {
            pinMode(pin, INPUT_PULLUP);
        } else {
            pinMode(pin, INPUT);
        }
    } else {

    }
}

void HbButton::setPin(int pin)
{
    this->pin = pin;
}

void HbButton::setMode(boolean isDigital, boolean isPullup)
{
    this->isDigital = isDigital;
    this->isPullup = isPullup;
}

void HbButton::setMode(boolean isDigital)
{
    this->isDigital = isDigital;
}

void HbButton::init()
{
    if (this->isDigital) {
        if (this->isPullup) {
            pinMode(this->pin, INPUT_PULLUP);
        } else {
            pinMode(this->pin, INPUT);
        }
    } else {
    }
}

void HbButton::attach(int pin, boolean isDigital, boolean isPullup)
{
    (this->setPin)(pin);
    (this->setMode)(isDigital, isPullup);
    (this->init)();
}

void HbButton::attach(int pin)
{
    (this->attach)(pin, true, true);
}

boolean HbButton::read()
{
    int count = 0;
    if (isDigital) {
        for(int i; i<HBBUTTON_MAX_COUNT; i++) {
            if (digitalRead(this->pin) == HIGH) count++;
        }
    } else {
        for(int i; i<HBBUTTON_MAX_COUNT; i++) {
            if (analogRead(this->pin) > 512) count++;
        }
    }

    if (2*count > HBBUTTON_MAX_COUNT) return HIGH;
    else return LOW;
}

boolean HbButton::readraw()
{
    if (isDigital) {
        return digitalRead(this->pin);
    } else {
        return analogRead(this->pin) > 512 ? HIGH : LOW;
    }
}
