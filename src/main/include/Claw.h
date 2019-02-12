#pragma once

#include <ctre/Phoenix.h>
#include <frc/Servo.h>

#define servoOpen       90
#define servoClosed     135

class Claw {
    public:

        Claw(int clawTalon, int clawServo);
        Claw(WPI_TalonSRX *clawTalon, frc::Servo *clawServo);

        void OpenServo();
        void CloseServo();
        void RetrieveBall();
        void EjectBall();

    private:
        WPI_TalonSRX *m_clawMotor;
        frc::Servo *m_clawServo;
};