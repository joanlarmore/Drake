#include "Arm.h"

Arm::Arm(int shoulderMotor, int elbowMotor, int turretMotor) {
    m_shoulderMotor = new rev::CANSparkMax(shoulderMotor, rev::CANSparkMax::MotorType::kBrushless);
    m_elbowMotor    = new rev::CANSparkMax(elbowMotor, rev::CANSparkMax::MotorType::kBrushless);
    m_turretMotor   = new WPI_TalonSRX(turretMotor);
}

Arm::Arm(rev::CANSparkMax *shoulderMotor, rev::CANSparkMax *elbowMotor, WPI_TalonSRX *turretMotor) {
    m_shoulderMotor = shoulderMotor;
    m_elbowMotor    = elbowMotor;
    m_turretMotor   = turretMotor;
}

void
Arm::FindArmAngles(float x, float y, float *ang1, float *ang2)
{
	float r = sqrt(x*x+y*y);
	*ang2   = acos((40*40+32*32-r*r)/(2*40*32));
	*ang1   = acos((32*32+r*r-40*40)/(2*32*r)) + atan(y/x);
}

void
Arm::FindArmMinMax(float baseMin, float baseMax, float *elbowMin, float *elbowMax) {
	*elbowMin = .38*((150-baseMin)/.8)+10;
	*elbowMax = .45*((150-baseMax)/.8)+110-*elbowMin;
}