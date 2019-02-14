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
    m_leftStick = new frc::Joystick(1);
    m_rightStick = new frc::Joystick(2);

    m_arm = new Arm(SHOULDER_MOTOR, ELBOW_MOTOR, TURRET_MOTOR);
    m_claw = new Claw(CLAW_MOTOR, 0); //clawServo is PWM...? I hard-coded the ID
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
    // m_drive->Cartesian(m_leftStick, m_rightStick, 0.0);

    //DELETE AFTER DONE TESTING (this is a temp class to find out what voltages correspond to what heights)
    //m_arm->TEMPCONTROL(m_leftStick->GetY() * .35);

    // this stuff is joshified code which is untested
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
