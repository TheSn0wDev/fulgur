#pragma once
#include <iostream>
#include <algorithm> 
#include "Controller.hpp"
#include "Logger.hpp"

const float DEADZONE = 0.05f;

class PS5Controller : public Controller {
    public:
        bool connect() override;
        void poll() override;
        std::string getName() const override;
        json getState() const override;

    private:
        Controller::Button getButton(SDL_GameControllerButton button) override;
        Controller::Axis getAxis(SDL_GameControllerAxis axis) override;
        void updateButtonState(Controller::Button button, bool pressed);
        void updateAxisState(Controller::Axis axis, float value);
        
        SDL_GameController* _controller = nullptr;
        SDL_JoystickID _instance_id = -1;
        json _state = {
            {"buttons", {
                {"A", false},
                {"B", false},
                {"X", false},
                {"Y", false},
                {"L1", false},
                {"R1", false},
                {"START", false},
                {"BACK", false},
                {"DPAD_UP", false},
                {"DPAD_DOWN", false},
                {"DPAD_LEFT", false},
                {"DPAD_RIGHT", false},
                {"LEFT_STICK", false},
                {"RIGHT_STICK", false},
                {"TOUCHPAD", false},
                {"GUIDE", false}
            }},
            {"axes", {
                {"LEFT_X", 0.0},
                {"LEFT_Y", 0.0},
                {"RIGHT_X", 0.0},
                {"RIGHT_Y", 0.0},
                {"L2", 0.0},
                {"R2", 0.0}
            }}
        };
};