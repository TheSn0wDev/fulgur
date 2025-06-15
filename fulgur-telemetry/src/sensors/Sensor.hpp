#pragma once
#include <string>

class Sensor {
    public:
        virtual ~Sensor() = default;
        virtual std::string name() const = 0;
        virtual float readValue() const = 0;
};