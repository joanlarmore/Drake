/*
 * ArmTest.h
 * 
 * Created Feb 16, 2019
 * 
 */

#pragma once

#include <string>
#include <frc/WPILib.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>

#define ARM_MOTOR_CID_TURRET 0
#define ARM_MOTOR_CID_SHOULDER 0
#define ARM_MOTOR_CID_ELBOW 0
#define ARM_MOTOR_CID_HAND 0

class ArmTest 
{
public:
    ArmTest(int TurretMotorChannel, int ShoulderMotorChannel,
            int ElbowMotorChannel, int HandMotorChannel,
            int TurretPotDIO, int HandServoPWM, int HandIRSensorDIO);
    ~ArmTest();
    
    void Periodic(frc::Joystick *LeftStick, frc::Joystick *RightStick);

private:
    WPI_TalonSRX        *m_turret;
    rev::CANSparkMax    *m_shoulder;
    frc::Potentiometer  *m_shoulderPot;
    WPI_TalonSRX        *m_elbow;
    WPI_TalonSRX        *m_hand;
    frc::Servo          *m_handServo;
    frc::DigitalInput   *m_handSensor;
};
