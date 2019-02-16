/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


// I AM CURRENTLY WORKING ON THE ARM CODE

#include <iostream>
#include "Drake.h"

float
DeadZone(float input, float range) {
    if (abs(input) < range) {
        return 0;
    } else {
        return input;
    }
}

void
Robot::RobotInit() 
{
    m_drive = new DalekDrive(1, 2, 3, 4, DalekDrive::driveType::kMecanum);
    m_leftStick = new frc::Joystick(1);
    m_rightStick = new frc::Joystick(2);
    m_xbox = new frc::XboxController(3);

    m_arm = new Arm(SHOULDER_MOTOR, ELBOW_MOTOR, TURRET_MOTOR);
    m_claw = new Claw(CLAW_MOTOR, 0);

}

void
Robot::RobotPeriodic() 
{
}

void
Robot::AutonomousInit() 
{
}

void
Robot::AutonomousPeriodic()
{
}

void
Robot::TeleopInit() 
{
}

void
Robot::TeleopPeriodic()
{
    m_drive->Cartesian(*m_leftStick, 0.0);
    // claw periodic function
    m_claw->Tick(m_xbox);


    //Motor Voltage values
    m_arm->printVoltage();
    m_claw->printVoltage();
}

void
Robot::TestPeriodic()
{
}

#ifndef RUNNING_FRC_TESTS
int
main() 
{ 
  return frc::StartRobot<Robot>();
}
#endif
