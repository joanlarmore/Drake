#include "Arm.h"

Arm::Arm(int shoulderMotor, int elbowMotor, int turretMotor) {
    m_shoulderMotor        = new CANSparkMax(shoulderMotor, CANSparkMax::MotorType::kBrushless);
    m_shoulderMotorEncoder = new CANEncoder(*m_shoulderMotor);
    m_elbowMotor           = new WPI_TalonSRX(elbowMotor);
    m_turretMotor          = new WPI_TalonSRX(turretMotor);
}

Arm::Arm(CANSparkMax *shoulderMotor, WPI_TalonSRX *elbowMotor, WPI_TalonSRX *turretMotor) {
    m_shoulderMotor        = shoulderMotor;
    m_elbowMotor           = elbowMotor;
    m_turretMotor          = turretMotor;
    m_shoulderMotorEncoder = new CANEncoder(*m_shoulderMotor);
}

void 
Arm::printVoltage()
{
    //min: .156 max: .158
    frc::SmartDashboard::PutNumber("Shoulder current", m_shoulderMotor->GetOutputCurrent());
    //min:.125 max:.375
    frc::SmartDashboard::PutNumber("Elbow current", m_elbowMotor->GetOutputCurrent());
    //min:.125 max:.8
    frc::SmartDashboard::PutNumber("Turret current", m_turretMotor->GetOutputCurrent());
}

void 
Arm::TEMP_ROTATE_SHOULDER(float voltage) {

    // std::cout << voltage << "\n";
    m_shoulderMotor->Set(voltage);
    std::cout << m_shoulderMotorEncoder->GetPosition() << "\n";
}

void
Arm::moveToPosition(float x, float y) {
    float ang1, ang2;
    if (FindArmAngles(x, y, &ang1, &ang2)) {
        shoulderAngle = ang1;
        elbowAngle = ang2;
        // m_shoulderMotor->Set();  //  <-- find voltage based off of angle by testing
        // m_elbowMotor->Set();     //  <-- ""
    } else {
        std::cout << "INVALID ANGLE";
    }

    // ^ these may need an offset for the zero position

}

void Arm::TEMP_ROTATE_ELBOW(float voltage) {
    m_elbowMotor->Set(voltage);
}

void Arm::TEMP_ROTATE_TURRET(float voltage){
    m_turretMotor->Set(voltage);
} 


void
Arm::moveToPosition(bool hasBall, int position) {
    // a bunch of ifs finding x and y based off of what position in unput, then calling the other MoveToPosition
    bool valid = true;
    float x, y;
    if (hasBall) {
        if (position == BALL_PICK_UP) {
            // x = something, y = something FOR ALL
        } else if (position == HATCH_PICK_UP) {

        } else if (position == CARGO_SHIP) {
            
        } else if (position == ROCKET_LOW) {

        } else if (position == ROCKET_MID) {

        } else if (position == ROCKET_HIGH) {

        } else {
            valid = false;
        }
    } else {
        if (position == BALL_PICK_UP) {
            
        } else if (position == HATCH_PICK_UP) {

        } else if (position == CARGO_SHIP) {
            
        } else if (position == ROCKET_LOW) {

        } else if (position == ROCKET_MID) {

        } else if (position == ROCKET_HIGH) {

        } else {
            valid = false;
        }
    }
    if (valid) {
        moveToPosition(x, y);
    } else {
        std::cout << "INVALID ANGLE";
    }
}

bool
Arm::FindArmAngles(float x, float y, float *ang1, float *ang2)
{
	float r = sqrt(x*x+y*y);
	*ang2   = acos((40*40+32*32-r*r)/(2*40*32));
	*ang1   = acos((32*32+r*r-40*40)/(2*32*r)) + atan(y/x);
    float elbowMin, elbowMax;
    FindArmMinMax(*ang1, &elbowMin, &elbowMax);
    return (*ang2 > elbowMin && *ang2 < elbowMax);
}

void
Arm::FindArmMinMax(float base, float *elbowMin, float *elbowMax) {
	*elbowMin = .38*((150-base)/.8)+10;
	*elbowMax = .45*((150-base)/.8)+110-*elbowMin;
}