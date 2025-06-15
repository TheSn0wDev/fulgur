#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Controller {
    public:
        enum class Button {
            A,
            B,
            X,
            Y,
            L1,
            R1,
            START,
            BACK,
            DPAD_UP,
            DPAD_DOWN,
            DPAD_LEFT,
            DPAD_RIGHT,
            LEFT_STICK,
            RIGHT_STICK,
            TOUCHPAD,
            GUIDE,
            UNKNOWN
        };

        enum class Axis {
            LEFT_X,
            LEFT_Y,
            RIGHT_X,
            RIGHT_Y,
            L2,
            R2,
            UNKNOWN
        };
        
        inline const std::string toString(Button button) {
            switch (button) {
                case Button::A:  return "A";
                case Button::B:  return "B";
                case Button::X:  return "X";
                case Button::Y:  return "Y";
                case Button::L1: return "L1";
                case Button::R1: return "R1";
                case Button::START: return "START";
                case Button::BACK: return "BACK";
                case Button::DPAD_UP: return "DPAD_UP";
                case Button::DPAD_DOWN: return "DPAD_DOWN";
                case Button::DPAD_LEFT: return "DPAD_LEFT";
                case Button::DPAD_RIGHT: return "DPAD_RIGHT";
                case Button::LEFT_STICK: return "LEFT_STICK";
                case Button::RIGHT_STICK: return "RIGHT_STICK";
                case Button::TOUCHPAD: return "TOUCHPAD";
                case Button::GUIDE: return "GUIDE";
                default: return "UNKNOWN";
            }
        }

        inline const std::string toString(Axis axis) {
            switch (axis) {
                case Axis::LEFT_X: return "LEFT_X";
                case Axis::LEFT_Y: return "LEFT_Y";
                case Axis::RIGHT_X: return "RIGHT_X";
                case Axis::RIGHT_Y: return "RIGHT_Y";
                case Axis::L2: return "L2";
                case Axis::R2: return "R2";
                default: return "UNKNOWN";
            }
        }
    
        virtual ~Controller() = default;
        virtual bool connect() = 0;
        virtual void poll() = 0;
        virtual std::string getName() const = 0;
        virtual json getState() const = 0;

    private:
        virtual Controller::Button getButton(SDL_GamepadButton button) = 0;
        virtual Controller::Axis getAxis(SDL_GamepadAxis axis) = 0;
};