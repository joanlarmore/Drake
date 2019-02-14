/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once


#include <string>
#include <frc/WPILib.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/XboxController.h>
#include <frc/Servo.h>
#include <frc/AnalogPotentiometer.h>
#include "DalekDrive.h"
#include "Arm.h"
#include "Claw.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  enum CLAW_LOCATIONS {BALL_PICK_UP, HATCH_PICK_UP, CARGO_SHIP, ROCKET_LOW, ROCKET_MID, ROCKET_HIGH}; // there is def a better way for this but this exact enum is in Arm.h
  enum CANIDs         {LEFT_FRONT_MOTOR = 1, LEFT_REAR_MOTOR, RIGHT_FRONT_MOTOR, RIGHT_REAR_MOTOR, SHOULDER_MOTOR, ELBOW_MOTOR, TURRET_MOTOR, CLAW_MOTOR};
  enum DIOS           {FRONT_LEFT_LIDAR = 0, FRONT_RIGHT_LIDAR, RIGHT_FRONT_LIDAR, RIGHT_REAR_LIDAR, LEFT_FRONT_LIDAR_, LEFT_REAR_LIDAR};

 private:
  DalekDrive *m_drive;
  Arm *m_arm;
  Claw *m_claw;
  frc::Joystick *m_leftStick;
  frc::Joystick *m_rightStick;
  frc::Joystick *m_fakeStick;
};
