
#pragma once
#include "Sensor.hpp"
#include <fstream>

class CPUTemperatureSensor : public Sensor {
public:
    std::string name() const override
    float readValue() const override;
};s