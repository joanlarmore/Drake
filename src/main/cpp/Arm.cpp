// for now, both motors will move into position at the same time... however this might need to change in order to keep in bounds and not hit walls in front of us 
// also in the moveToPosition, make sure the base angle is allowed on the robot, and otherwise make valid false

#include "Arm.h"

Arm::Arm(int shoulderMotor, int elbowMotor, int turretMotor, int shoulderPot)
{
    m_shoulderMotor        = new CANSparkMax(shoulderMotor, CANSparkMax::MotorType::kBrushless);
    m_elbowMotor           = new WPI_TalonSRX(elbowMotor);
    m_turretMotor          = new WPI_TalonSRX(turretMotor);
    m_shoulderPot          = new AnalogPotentiometer(shoulderPot, 1.0, 0.0); // maybe change the full range
    m_shoulderMotorEncoder = new CANEncoder(*m_shoulderMotor);
}

Arm::Arm(CANSparkMax *shoulderMotor, WPI_TalonSRX *elbowMotor, WPI_TalonSRX *turretMotor, Potentiometer *shoulderPot)
{
    m_shoulderMotor        = shoulderMotor;
    m_elbowMotor           = elbowMotor;
    m_turretMotor          = turretMotor;
    m_shoulderPot          = shoulderPot;
    m_shoulderMotorEncoder = new CANEncoder(*m_shoulderMotor);
}

void Arm::Tick(XboxController *xbox, POVButton *dPad[])
{
    m_turretMotor->Set(xbox->GetX(GenericHID::JoystickHand::kRightHand) * .5);
    float x, y;
    bool move = true;
    if (xbox->GetAButton()) {
        if (dPad[R]->Get()) {
            x = defaultX;
            y = rocketHatchLowHeight;
        } else if (dPad[T]->Get()) {
            x = cargoBallLength;
            y = cargoBallHeight;
        } else if (dPad[L]->Get()) {
            x = defaultX;
            y = cargoHatchHeight;
        } else if (dPad[B]->Get()) {
            x = defaultX;
            y = rocketBallLowHeight;
        } else {
            move = false;
        }
    } else if (xbox->GetBButton()) {
        if (dPad[R]->Get() || dPad[T]->Get() || dPad[L]->Get() || dPad[B]->Get()) {
            x = defaultX;
            y = ballLoadHeight;
        } else {
            x = ballPickUpX;
            y = ballPickUpY;
        }
    } else if (xbox->GetXButton()) {
        if (dPad[R]->Get()) {
            x = defaultX;
            y = rocketHatchMiddleHeight;
        } else if (dPad[B]->Get()) {
            x = defaultX;
            y = rocketBallMiddleHeight;
        } else {
            move = false;
        }
    } else if (xbox->GetYButton()) {
        if (dPad[R]->Get()) {
            x = defaultX;
            y = rocketHatchTopHeight;
        } else if (dPad[B]->Get()) {
            x = defaultX;
            y = rocketBallTopHeight;
        } else {
            move = false;
        }
    } else if (xbox->GetTriggerAxis(GenericHID::JoystickHand::kRightHand) > .1) {
        // FETAL POSITION
    } else {
        x = curX + xbox->GetY(GenericHID::JoystickHand::kRightHand) * .5; // .5 is a guess... fix in testing
        y = curY + xbox->GetY(GenericHID::JoystickHand::kLeftHand) * .5;  // same as above
        if (x == curX && y == curY) {
            move = false;
        }
    }
    if (move) {
        moveToPosition(x, y);
    }
    SetMotors();
}

void
Arm::moveToPosition(float x, float y)
{
    float ang1 = -1, ang2 = -1;
    if (FindArmAngles(x, y, &ang1, &ang2)) {
        shoulderAngle = ang1;
        elbowAngle = ang2;
        curX = x;
        curY = y;
        std::cout << "MOVING TO: x = " << x << ", y = " << y << ", ang1 = " << ang1 << ", ang2 = " << ang2 << "\n";
    } else {
        std::cout << "INVALID ANGLE: x = " << x << ", y = " << y << ", ang1 = " << ang1 << ", ang2 = " << ang2 << "\n";
    }
}

void
Arm::SetMotors() {
    // here the shoulderAngle and elbowAngle are updated, so they need to be converted into Set() (i think just experimentation)
    // i think use the method below for elbow
    // m_elbowMotor->Set(ctre::phoenix::motorcontrol::ControlMode::Position, 0); // the second number is the voltage [0-3.3] i think
    // the shoulder has a shoulderPot as an analog input so that needs a manual configuration, but i think that is just full speed toward the angle?
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
	*ang2 = acos((highArmLength * highArmLength + lowArmLength * lowArmLength - r * r) / (2 * highArmLength * lowArmLength));
	*ang1 = acos((lowArmLength * lowArmLength + r * r - highArmLength * highArmLength) / (2 * lowArmLength * r)) + atan(y / x);
    float elbowMin, elbowMax;
    FindArmMinMax(*ang1, &elbowMin, &elbowMax);
    return (*ang1 > 0 && *ang2 > 0) && (*ang2 > elbowMin && *ang2 < elbowMax); // the first part is making sure they are both not nan
}

void
Arm::FindArmMinMax(float base, float *elbowMin, float *elbowMax)
{
	*elbowMin = .38*((150.0-base)/.8)+10.0;
	*elbowMax = .45*((150.0-base)/.8)+110.0-*elbowMin;
}

void 
Arm::printVoltage()
{
    //min: .156 max: .158
    SmartDashboard::PutNumber("Shoulder current", m_shoulderMotor->GetOutputCurrent());
    //min:.125 max:.375
    SmartDashboard::PutNumber("Elbow current", m_elbowMotor->GetOutputCurrent());
    //min:.125 max:.8
    SmartDashboard::PutNumber("Turret current", m_turretMotor->GetOutputCurrent());
}