/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include <iostream>
#include "Drake.h"


void
Robot::RobotInit() 
{
    
    m_drive = new DalekDrive(1, 2, 3, 4, DalekDrive::driveType::kMecanum);
    m_leftStick = new frc::Joystick(0);
    m_rightStick = new frc::Joystick(1);
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
    // pick one to test, all should in principle work for the mecanum wheels
    //m_drive->TankDrive(m_leftStick, m_rightStick, false);
    //m_drive->Polar(m_leftStick, m_rightStick);
    m_drive->Cartesian(m_leftStick, m_rightStick, 0.0);
    //m_drive->SetLeftRightMotorOutputs(m_leftStick->GetY(), -m_rightStick->GetY());

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
