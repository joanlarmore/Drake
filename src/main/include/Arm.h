#pragma once

// claw servo position must be public or have a public get function

#include <iostream>
#include <Math.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/AnalogPotentiometer.h>
#include <frc/buttons/POVButton.h>
#include <frc/XboxController.h>

#include <frc/smartdashboard/SendableChooser.h>
#include "frc/smartdashboard/SmartDashBoard.h"

using namespace rev;

// in millimeters (check these)
#define armBaseHeight             343
#define armBaseFrontX             445
#define armBaseSideX              358
#define clawLength                165
#define maxLowArmAngle            150
#define minLowArmAngle            70
#define lowArmLength              813
#define highArmLength             1016
#define defaultX                  190                    // i made this up
#define cargoHatchHeight           381          // 1
#define cargoBallHeight           1219         // 2
#define cargoBallLength           750                    // i made this up
#define rocketHatchLowHeight       483  // check   3
#define rocketBallLowHeight       699//           4
#define rocketHatchMiddleHeight    1194//          5
#define rocketBallMiddleHeight    1410//          6
#define rocketHatchTopHeight       1905//          7
#define rocketBallTopHeight       2121//          8
#define ballPickUpX               279 //guess     9
#define ballPickUpY               165 //guess
#define discLoadHeight            381//          10      not used for controls
#define ballLoadHeight            0 //unknown    11      WRITE THIS ONE

enum POVButtons {R, T, L, B};

using namespace frc;

class Arm {
  public:
    float shoulderAngle, elbowAngle, curX, curY;

    Arm(int shoulderMotor, int elbowMotor, int turretMotor, int shoulderPot);
    Arm(CANSparkMax *shoulderMotor, WPI_TalonSRX *elbowMotor, WPI_TalonSRX *turretMotor, Potentiometer *shoulderPot);

    void Tick(XboxController *xbox, POVButton *dPad[4]); // check dpad syntax
    void moveToPosition(float x, float y);
    void printVoltage();
  
  private:
    CANSparkMax *m_shoulderMotor;
    CANEncoder *m_shoulderMotorEncoder;
    WPI_TalonSRX *m_elbowMotor, *m_turretMotor;
    //  *m_elbowPot, *m_turretPot;
    Potentiometer *m_shoulderPot;
 
    void SetMotors();
    bool FindArmAngles(float x, float y, float *ang1, float *ang2);
    void FindArmMinMax(float base, float *elbowMin, float *elbowMax);
};

