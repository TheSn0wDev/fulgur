#include "CPUTemperatureSensor.hpp"

CPUTemperatureSensor::name() const {
    return "cpu_temp";
}

CPUTemperatureSensor::readValue() const {
    std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open temperature file");
    }

    float temp;
    file >> temp;
    file.close();

    return temp / 1000.0f;
}