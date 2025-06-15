#include "PS5Controller.hpp"

bool PS5Controller::connect() {
    SDL_SetHint(SDL_HINT_JOYSTICK_ENHANCED_REPORTS, "1");
    
    if (!SDL_Init(SDL_INIT_GAMEPAD)) { 
        Logger::error("Failed to initialize SDL: " + std::string(SDL_GetError()));
        return false;
    } 

    SDL_UpdateGamepads();

    int numJoysticks = 0;
    SDL_JoystickID *joysticksIds = SDL_GetJoysticks(&numJoysticks);

    for (int i = 0; i < numJoysticks; ++i) {
        SDL_JoystickID id = joysticksIds[i];

        if (SDL_IsGamepad(id)) {
            Logger::debug("Found gamepad: " + std::string(SDL_GetGamepadNameForID(id)));
            _instance_id = id;
            break;
        }
    }

    if (!(_controller = SDL_OpenGamepad(_instance_id))) {
        Logger::error("Failed to open PS5 controller: " + std::string(SDL_GetError()));
        return false;
    }

    return true;
}

void PS5Controller::poll() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN || e.type == SDL_EVENT_GAMEPAD_BUTTON_UP) {
            if (e.gbutton.which != _instance_id) continue;

            Controller::Button button = this->getButton(static_cast<SDL_GamepadButton>(e.gbutton.button));
            bool pressed = (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN);

            this->updateButtonState(button, pressed);
        }

        if (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
            if (e.gaxis.which != _instance_id) continue;

            SDL_GamepadAxis axis = static_cast<SDL_GamepadAxis>(e.gaxis.axis);
            int rawValue = e.gaxis.value;

            float normalized = 0.0f;
            if (axis == SDL_GAMEPAD_AXIS_LEFTX || axis == SDL_GAMEPAD_AXIS_LEFTY ||
                axis == SDL_GAMEPAD_AXIS_RIGHTX || axis == SDL_GAMEPAD_AXIS_RIGHTY ||
                axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER || axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) {
                normalized = std::clamp(rawValue / 32767.0f, -1.0f, 1.0f);
            }

            if (std::abs(normalized) < DEADZONE) {
                normalized = 0.0f;
            }

            this->updateAxisState(this->getAxis(axis), normalized);
        }

        if (e.type == SDL_EVENT_JOYSTICK_BATTERY_UPDATED) {
            if (e.jbattery.which != _instance_id) continue;

            int percentage = 0;
            SDL_PowerState power = SDL_GetGamepadPowerInfo(_controller, &percentage);

            this->updateBatteryState(percentage, (power == SDL_POWERSTATE_NO_BATTERY || power == SDL_POWERSTATE_CHARGING || power == SDL_POWERSTATE_CHARGED));
        }
    }
}

std::string PS5Controller::getName() const {
    return this->_controller ? SDL_GetGamepadName(_controller) : "PS5 Controller";
}

Controller::Button PS5Controller::getButton(SDL_GamepadButton button) {
    switch (button) {
        case SDL_GAMEPAD_BUTTON_SOUTH: return Controller::Button::A;
        case SDL_GAMEPAD_BUTTON_EAST: return Controller::Button::B;
        case SDL_GAMEPAD_BUTTON_WEST: return Controller::Button::X;
        case SDL_GAMEPAD_BUTTON_NORTH: return Controller::Button::Y;
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER: return Controller::Button::L1;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: return Controller::Button::R1;
        case SDL_GAMEPAD_BUTTON_START: return Controller::Button::START;
        case SDL_GAMEPAD_BUTTON_BACK: return Controller::Button::BACK;
        case SDL_GAMEPAD_BUTTON_DPAD_UP: return Controller::Button::DPAD_UP;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN: return Controller::Button::DPAD_DOWN;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT: return Controller::Button::DPAD_LEFT;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: return Controller::Button::DPAD_RIGHT;
        case SDL_GAMEPAD_BUTTON_LEFT_STICK: return Controller::Button::LEFT_STICK;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK: return Controller::Button::RIGHT_STICK;
        case SDL_GAMEPAD_BUTTON_TOUCHPAD: return Controller::Button::TOUCHPAD;
        case SDL_GAMEPAD_BUTTON_GUIDE: return Controller::Button::GUIDE;
        default: return Controller::Button::UNKNOWN;
    }
}

Controller::Axis PS5Controller::getAxis(SDL_GamepadAxis axis) {
    switch (axis) {
        case SDL_GAMEPAD_AXIS_LEFTX: return Controller::Axis::LEFT_X;
        case SDL_GAMEPAD_AXIS_LEFTY: return Controller::Axis::LEFT_Y;
        case SDL_GAMEPAD_AXIS_RIGHTX: return Controller::Axis::RIGHT_X;
        case SDL_GAMEPAD_AXIS_RIGHTY: return Controller::Axis::RIGHT_Y;
        case SDL_GAMEPAD_AXIS_LEFT_TRIGGER: return Controller::Axis::L2;
        case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER: return Controller::Axis::R2;
        default: return Controller::Axis::UNKNOWN;
    }
}

json PS5Controller::getState() const {
    return _state;
}

void PS5Controller::updateButtonState(Controller::Button button, bool pressed) {
    std::string buttonName = toString(button);
    _state["buttons"][buttonName] = pressed;
}

void PS5Controller::updateAxisState(Controller::Axis axis, float value) {
    std::string axisName = toString(axis);
    _state["axes"][axisName] = value;
}

void PS5Controller::updateBatteryState(int level, bool isCharging) {
    std::cout << "Battery level: " << level << ", Charging: " << (isCharging ? "Yes" : "No") << std::endl;
    _state["battery"]["level"] = level;
    _state["battery"]["isCharging"] = isCharging;
}