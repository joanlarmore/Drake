#pragma once

#include <iostream>
#include <ctre/Phoenix.h>
#include <frc/Servo.h>
// #include <DigitalInput.h>

#define servoOpen       90
#define servoClosed     135

using namespace frc;

class Claw {
    public:

        // Claw(int clawTalon, int clawServo, int clawLimit);
        // Claw(WPI_TalonSRX *clawTalon, Servo *clawServo, DigitalInput *clawLimit);
        Claw(int clawTalon, int clawServo);
        Claw(WPI_TalonSRX *clawTalon, Servo *clawServo);

        void OpenServo();
        void CloseServo();
        void RetrieveBall();
        void EjectBall();

    private:
        WPI_TalonSRX *m_clawMotor;
        Servo *m_clawServo;
        // DigitalInput *m_clawLimit;        <-- if the limit switch is a DIO (otherwise i think it is purely electrical)
};