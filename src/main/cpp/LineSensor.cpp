#include "LineSensor.h"

LineSensor::LineSensor() {
    init();
}
LineSensor::~LineSensor() {

}


void LineSensor::init() {
    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        digitalInputArray[i] = new frc::DigitalInput(i + 10);
    }
}


bool LineSensor::getLineSensor(int lineSensorNumber) {
    return !digitalInputArray[lineSensorNumber]->Get();
}