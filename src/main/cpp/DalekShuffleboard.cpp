#include "DalekShuffleboard.h"

DalekShuffleboard::DalekShuffleboard(MicroLidar *microLidar) {
    this->microLidar = microLidar;
    init();
}
DalekShuffleboard::~DalekShuffleboard() {

}



void DalekShuffleboard::init() {

    for (int i = 0; i < LIDAR_COUNT; i++) {
        std::string temp = "Lidar " + std::to_string(i) + " Reset";
        frc::SmartDashboard::PutBoolean(temp, resetLidar[i]);
    }
    
    frc::SmartDashboard::PutBoolean("Allow Lidar Reset", calibrateLidar);
}

void DalekShuffleboard::continious() {
    calibrateLidar = frc::SmartDashboard::GetBoolean("Allow Lidar Reset", false);
    if (calibrateLidar) {
        for (int i = 0; i < LIDAR_COUNT; i++) {
            std::string temp = "Lidar " + std::to_string(i) + " Reset";
            resetLidar[i] = frc::SmartDashboard::GetBoolean(temp, false);
            if (resetLidar[i]) {
                //Callibrate Lidar Sensors
                resetLidar[i] = false;
                frc::SmartDashboard::PutBoolean(temp, resetLidar[i]);
            }
        }
    }

    frc::SmartDashboard::PutNumber("Lidar Sensor: 0", microLidar->GetMeasurement(0));
    frc::SmartDashboard::PutNumber("Lidar Sensor: 1", microLidar->GetMeasurement(1));
    frc::SmartDashboard::PutNumber("Lidar Sensor: 2", microLidar->GetMeasurement(2));
    frc::SmartDashboard::PutNumber("Lidar Sensor: 3", microLidar->GetMeasurement(3));
    frc::SmartDashboard::PutNumber("Lidar Sensor: 4", microLidar->GetMeasurement(4));
    frc::SmartDashboard::PutNumber("Lidar Sensor: 5", microLidar->GetMeasurement(5));
}