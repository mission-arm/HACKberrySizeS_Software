#include <Arduino.h>
#include <Servo.h>

#include "HACKberry.h"
#include "HbButton.h"
#include "HbSensor.h"

// Objects
HACKberry Hb;

void setup() {

    // Object initialization
    Hb.setBoardType(SizeSLeft);
    Hb.setAngleIndex( 80,170);
    Hb.setAngleOther(105,145);
    Hb.setAngleThumb( 70, 80);
    Hb.setSpeedRange( 6, 0, -2, -4); //
    Hb.setSensorThreshold(150, 30); //
    Hb.init();
    delay(100);

    // Sensor Calibration
    Hb.ServoIndex.write(Hb.AngleIndexOpen);
    Hb.ServoOther.write(Hb.AngleOtherOpen);
    Hb.ServoThumb.write(Hb.AngleThumbOpen);

    delay(100);

    while (1) {
        if (Hb.ButtonCalib.read() == LOW) {
            Hb.calibration(5000);
            break;
        }
    }
}

void loop() {
    // Control
    while (true) {

        // Button
        if (Hb.ButtonCalib.read() == LOW) {
            Hb.calibration(5000);
            while (Hb.ButtonCalib.read() == LOW) delay(1);
        }

        if (Hb.ButtonExtra.read() == LOW) {
            // do something here
            while (Hb.ButtonExtra.read() == LOW) delay(1);
        }

        if (Hb.ButtonThumb.read() == LOW) {
            Hb.isThumbOpen = !Hb.isThumbOpen;
            while(Hb.ButtonThumb.read() == LOW) delay(1);
        }

        if (Hb.ButtonOther.read() == LOW) {
            Hb.isOtherLock = !Hb.isOtherLock;
            while(Hb.ButtonOther.read() == LOW) delay(1);
        }

        // sensor
        Hb.readSensor();
        Hb.calcPosition();

        // calc target angle
        Hb.TargetAngleIndex = map(Hb.angle_position,
                                    Hb.NormalizedAngleMinPosition, Hb.NormalizedAngleMaxPosition,
                                    Hb.AngleIndexOpen, Hb.AngleIndexClose);
        if ( Hb.isOtherLock ) {
            Hb.TargetAngleOther = Hb.TargetAngleOther;
        } else {
            Hb.TargetAngleOther = map(Hb.angle_position,
                                        Hb.NormalizedAngleMinPosition, Hb.NormalizedAngleMaxPosition,
                                        Hb.AngleOtherOpen, Hb.AngleOtherClose);
        }
        if ( Hb.isThumbOpen ) {
            Hb.TargetAngleThumb = Hb.AngleThumbOpen;
        } else {
            Hb.TargetAngleThumb = Hb.AngleThumbClose;
        }

        // servo control
        Hb.controlServo();
    }
}
