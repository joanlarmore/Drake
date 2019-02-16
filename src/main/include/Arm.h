#pragma once

// claw servo position must be public or have a public get function

#include <iostream>
#include <Math.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/AnalogPotentiometer.h>
#include <frc/XboxController.h>

#include <frc/smartdashboard/SendableChooser.h>
#include "frc/smartdashboard/SmartDashBoard.h"

using namespace rev;

// in centemeters
#define armBaseHeight             343;
#define armBaseFrontX             445;
#define armBaseSideX              358;
#define clawLength                165;
#define maxLowArmAngle            150;
#define minLowArmAngle            70;
#define lowArmLength              813;
#define highArmLength             1016;
#define cargoDiskHeight           381;          // 1
#define cargoBallHeight           1219;         // 2
#define rocketDiskLowHeight       483;  // check   3
#define rocketBallLowHeight       699;//           4
#define rocketDiskMiddleHeight    1194;//          5
#define rocketBallMiddleHeight    1410;//          6
#define rocketDiskTopHeight       1905;//          7
#define rocketBallTopHeight       2121;//          8
#define ballPickUpX               279; //same      9
#define ballPickUpY               165; //gueuss
#define discLoadHeight            381;//          10
#define ballLoadHeight            0; //unknown    11

using namespace frc;

class Arm {
  public:
    float shoulderAngle, elbowAngle, curX, curY;

    Arm(int shoulderMotor, int elbowMotor, int turretMotor);
    Arm(CANSparkMax *shoulderMotor, WPI_TalonSRX *elbowMotor, WPI_TalonSRX *turretMotor);

    void Tick(XboxController *xbox);
    void moveToPosition(bool hasBall, int position); // position is  from enum DROP_LOCATIONS
    void moveToPosition(float x, float y);
    void printVoltage();
  
  private:
    CANSparkMax *m_shoulderMotor;
    CANEncoder *m_shoulderMotorEncoder;
    WPI_TalonSRX *m_elbowMotor, *m_turretMotor;
      *m_elbowPot, *m_turretPot;
    frc::Potentiometer *m_shoulderPot; //Setup to roboRio analog input 0 <-- this was here before idk but also check pots
    // AnalogInput *; // <-- check where they are on the arm / limit switches (maybe pots?)
 
    bool FindArmAngles(float x, float y, float *ang1, float *ang2);
    void FindArmMinMax(float base, float *elbowMin, float *elbowMax);
    // prob need a method to convert elbow angles to voltage
};

