#include "Claw.h"

Claw::Claw(int clawMotor, int clawServo) {
    m_clawMotor = new WPI_TalonSRX(clawMotor);

}

Claw::Claw(WPI_TalonSRX *clawMotor, frc::Servo *clawServo) {
    
}