#include "ArmTest.h"

using namespace rev;
using namespace frc;

ArmTest::ArmTest(int TurretMotorChannel, int ShoulderMotorChannel,
                 int ElbowMotorChannel, int HandMotorChannel,
                 int TurretPotAIO, int HandServoPWM, int HandIRSensorDIO)
{
    m_turret        = new WPI_TalonSRX(TurretMotorChannel);
    m_shoulder      = new CANSparkMax(ShoulderMotorChannel, CANSparkMax::MotorType::kBrushless);
    m_elbow         = new WPI_TalonSRX(ElbowMotorChannel);
    m_hand          = new WPI_TalonSRX(HandMotorChannel);
    //m_shoulderPot   = new Potentiometer();
    m_handServo     = new Servo(HandServoPWM);
    m_handSensor    = new DigitalInput(HandIRSensorDIO);
}

ArmTest::~ArmTest()
{
    delete m_turret;
    delete m_shoulder;
    //delete m_shoulderPot;
    delete m_elbow;
    delete m_hand;
    delete m_handServo;
    delete m_handSensor;
}

void ArmTest::Periodic(frc::Joystick *LeftStick, frc::Joystick *RightStick)
{
    m_turret->Set(LeftStick->GetX());
    m_shoulder->Set(LeftStick->GetY());
    m_elbow->Set(RightStick->GetY());
    m_hand->Set(RightStick->GetX());
}