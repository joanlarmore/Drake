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

void Arm::Tick(XboxController *xbox) {
    m_turretMotor->Set(xbox->GetX(frc::GenericHID::JoystickHand::kRightHand) * .5);

    //fine movement first
    float yAxisShift = xbox->GetY(frc::GenericHID::JoystickHand::kLeftHand) * .5; // .5 is a guess... fix in testing
    float xAxisShift = xbox->GetY(frc::GenericHID::JoystickHand::kRightHand) * .5; // same as above
    //here calc where the result should end up and store into the xCur. yCur, and angles i think


    // then picked location sensing
    float x, y;
    bool move = true;
    // here should be a bunch of if-else  statements taking xbox controller and turning them into a x, y value, else move = false
    if (move) {
        moveToPosition(x, y);
    }
    // convert shoulderAngle and elbowAngle into moving the arm





    // test
    m_elbowMotor->Set(ctre::phoenix::motorcontrol::ControlMode::Position, 3.3); // the second number is the voltage
}

void
Arm::moveToPosition(float x, float y) {
    float ang1 = -1, ang2 = -1;
    if (FindArmAngles(x, y, &ang1, &ang2)) {
        shoulderAngle = ang1;
        elbowAngle = ang2;
        curX = x;
        curY = y;
    } else {
        std::cout << "INVALID ANGLE";
    }
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

// this function takes in the x distance from the target (starting from the edge of the drive train), and the y from the ground
bool
Arm::FindArmAngles(float x, float y, float *ang1, float *ang2)
{
	y -= armBaseHeight;
    //                                                           TODO:
    //                                                           make the x value vary based on where the turret is (for now i assume it is facing forward)
    x += armBaseFrontX - clawLength; //                          <-- here
    float r = sqrt(x*x+y*y);
    float low = lowArmLength;
    float high = highArmLength;
	*ang2 = acos((high*high+low*low-r*r)/(2*high*low));
	*ang1 = acos((low*low+r*r-high*high)/(2*low*r)) + atan(y/x);
    float elbowMin, elbowMax;
    FindArmMinMax(*ang1, &elbowMin, &elbowMax);
    return (*ang1 > 0 && *ang2 > 0) && (*ang2 > elbowMin && *ang2 < elbowMax); // the first part is making sure they are both not nan
}

void
Arm::FindArmMinMax(float base, float *elbowMin, float *elbowMax) {
	*elbowMin = .38*((150.0-base)/.8)+10.0;
	*elbowMax = .45*((150.0-base)/.8)+110.0-*elbowMin;
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