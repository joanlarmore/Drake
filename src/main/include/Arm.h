#pragma once

// claw servo position must be public or have a public get function

#include <Math.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/AnalogPotentiometer.h>

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

class Arm {
  public:

    Arm(int shoulderMotor, int elbowMotor, int turretMotor);
    Arm(rev::CANSparkMax *shoulderMotor, rev::CANSparkMax *elbowMotor, WPI_TalonSRX *turretMotor);

    
  
  private:
    rev::CANSparkMax *m_shoulderMotor, *m_elbowMotor;
    rev::CANEncoder *m_shoulderMotorEncoder, *m_elbowMotorEncoder;
    WPI_TalonSRX *m_turretMotor;
    frc::Potentiometer *m_shoulderPot, *m_elbowPot, *m_turretPot; //Setup to roboRio analog input 0 <-- this was here before idk but also check pots
    // AnalogInput *; // <-- check where they are on the arm / limit switches (maybe pots?)
 
    void FindArmAngles(float x, float y, float *ang1, float *ang2);
    void FindArmMinMax(float baseMin, float baseMax, float *elbowMin, float *elbowMax);
};

