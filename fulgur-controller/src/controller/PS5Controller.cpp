#include "PS5Controller.hpp"

bool PS5Controller::connect() {
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        Logger::error("Failed to initialize SDL: " + std::string(SDL_GetError()));
        return false;
    }

    if (SDL_NumJoysticks() < 1) {
        Logger::error("No controller detected.");
        return false;
    }
    
    _controller = SDL_GameControllerOpen(0);

    if (!_controller) {
        Logger::error("Failed to open PS5 controller: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_Joystick* joystick = SDL_GameControllerGetJoystick(_controller);
    _instance_id = SDL_JoystickInstanceID(joystick);

    return true;
}

void PS5Controller::poll() {
    SDL_Event e;
    
    while (SDL_PollEvent(&e)) {        
        if (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP) {
            if (e.cbutton.which != _instance_id) continue;

            Controller::Button button = this->getButton(static_cast<SDL_GameControllerButton>(e.cbutton.button));
            
            bool pressed = (e.type == SDL_CONTROLLERBUTTONDOWN);

            this->updateButtonState(button, pressed);
        } 
        
        if (e.type == SDL_CONTROLLERAXISMOTION) {
            SDL_GameControllerAxis axis = static_cast<SDL_GameControllerAxis>(e.caxis.axis);
            int rawValue = e.caxis.value;
            
            float normalized = 0.0f;
            
            if (axis == SDL_CONTROLLER_AXIS_LEFTX || axis == SDL_CONTROLLER_AXIS_LEFTY ||
                axis == SDL_CONTROLLER_AXIS_RIGHTX || axis == SDL_CONTROLLER_AXIS_RIGHTY ||
                axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT || axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
                normalized = std::clamp(rawValue / 32767.0f, -1.0f, 1.0f);
            }

            if (std::abs(normalized) < DEADZONE) {
                normalized = 0.0f;
            }

            this->updateAxisState(this->getAxis(axis), normalized);
        }
    }
}
    
std::string PS5Controller::getName() const {
    return "PS5 DualSense";
}

Controller::Button PS5Controller::getButton(SDL_GameControllerButton button) {
    switch (button) {
        case SDL_CONTROLLER_BUTTON_A: return Controller::Button::A;
        case SDL_CONTROLLER_BUTTON_B: return Controller::Button::B;
        case SDL_CONTROLLER_BUTTON_X: return Controller::Button::X;
        case SDL_CONTROLLER_BUTTON_Y: return Controller::Button::Y;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: return Controller::Button::L1;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return Controller::Button::R1;
        case SDL_CONTROLLER_BUTTON_START: return Controller::Button::START;
        case SDL_CONTROLLER_BUTTON_BACK: return Controller::Button::BACK;
        case SDL_CONTROLLER_BUTTON_DPAD_UP: return Controller::Button::DPAD_UP;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return Controller::Button::DPAD_DOWN;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return Controller::Button::DPAD_LEFT;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return Controller::Button::DPAD_RIGHT;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK: return Controller::Button::LEFT_STICK;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK: return Controller::Button::RIGHT_STICK;
        case SDL_CONTROLLER_BUTTON_TOUCHPAD: return Controller::Button::TOUCHPAD;
        case SDL_CONTROLLER_BUTTON_GUIDE: return Controller::Button::GUIDE;
        default: return Controller::Button::UNKNOWN;
    }
}

Controller::Axis PS5Controller::getAxis(SDL_GameControllerAxis axis) {
    switch (axis) {
        case SDL_CONTROLLER_AXIS_LEFTX: return Controller::Axis::LEFT_X;
        case SDL_CONTROLLER_AXIS_LEFTY: return Controller::Axis::LEFT_Y;
        case SDL_CONTROLLER_AXIS_RIGHTX: return Controller::Axis::RIGHT_X;
        case SDL_CONTROLLER_AXIS_RIGHTY: return Controller::Axis::RIGHT_Y;
        case SDL_CONTROLLER_AXIS_TRIGGERLEFT: return Controller::Axis::L2;
        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT: return Controller::Axis::R2;
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