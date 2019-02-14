#include "Claw.h"

// Claw::Claw(int clawMotor, int clawServo, int clawLimit) {
//     m_clawMotor = new WPI_TalonSRX(clawMotor);
//     m_clawServo = new Servo(clawServo);
//     m_clawLimit = new DigitalInput(clawLimit);
// }

// Claw::Claw(WPI_TalonSRX *clawMotor, Servo *clawServo, DigitalInput *clawLimit) {
//     m_clawMotor = clawMotor;
//     m_clawServo = clawServo;
//     m_clawLimit = clawLimit;
// }

Claw::Claw(int clawMotor, int clawServo) {
    m_clawMotor = new WPI_TalonSRX(clawMotor);
    m_clawServo = new Servo(clawServo);
}

Claw::Claw(WPI_TalonSRX *clawMotor, Servo *clawServo) {
    m_clawMotor = clawMotor;
    m_clawServo = clawServo;
}

void
Claw::OpenServo() {
    m_clawServo->SetAngle(servoOpen);
}

void 
Claw::CloseServo() {
    m_clawServo->SetAngle(servoClosed);
}

// both of these methods are written in a way where they must be continuously called in order to work
void
Claw::RetrieveBall() {
    // int set = 1;                        // or negative
    // if (m_clawLimit->Get()) {
    //     set = 0;
    // }
    // m_clawMotor->Set(set);
    m_clawMotor->Set(1);               // or negative
}

void
Claw::EjectBall() {
    m_clawMotor->Set(-1);              // or positive
}