#pragma once

// claw servo position must be public or have a public get function

#include <iostream>
#include <Math.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/AnalogPotentiometer.h>
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
#define cargoDiskHeight           381;
#define cargoBallHeight           1219;
#define rocketDiskLowHeight       483;
#define rocketBallLowHeight       699;
#define rocketDiskMiddleHeight    1194;
#define rocketBallMiddleHeight    1410;
#define rocketDiskTopHeight       1905;
#define rocketBallTopHeight       2121;
//#define ballPickUpX               279;
//#define ballPickUpY               165;
#define discLoadHeight            381;

enum CLAW_LOCATIONS {BALL_PICK_UP, HATCH_PICK_UP, CARGO_SHIP, ROCKET_LOW, ROCKET_MID, ROCKET_HIGH}; // there is def a better way for this but this exact enum is in Drake.h

class Arm {
  public:
    float shoulderAngle, elbowAngle;

    Arm(int shoulderMotor, int elbowMotor, int turretMotor);
    Arm(CANSparkMax *shoulderMotor, WPI_TalonSRX *elbowMotor, WPI_TalonSRX *turretMotor);

    void moveToPosition(bool hasBall, int position); // position is  from enum DROP_LOCATIONS
    void TEMP_ROTATE_SHOULDER(float voltage);
    void TEMP_ROTATE_TURRET(float voltage);
    void TEMP_ROTATE_ELBOW(float voltage);
    void printVoltage();
  
  private:
    CANSparkMax *m_shoulderMotor;
    CANEncoder *m_shoulderMotorEncoder;
    WPI_TalonSRX *m_elbowMotor, *m_turretMotor;
    frc::Potentiometer *m_shoulderPot, *m_elbowPot, *m_turretPot; //Setup to roboRio analog input 0 <-- this was here before idk but also check pots
    // AnalogInput *; // <-- check where they are on the arm / limit switches (maybe pots?)
 
    void moveToPosition(float x, float y);
    bool FindArmAngles(float x, float y, float *ang1, float *ang2);
    void FindArmMinMax(float base, float *elbowMin, float *elbowMax);
    // prob need a method to convert elbow angles to voltage
};

