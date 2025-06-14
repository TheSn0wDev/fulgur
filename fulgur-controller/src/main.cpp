#include <memory>
#include <thread>
#include <chrono>
#include <iostream>
#include <csignal>
#include <atomic>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL.h>
#include "NatsMessagingBus.hpp"
#include "controller/PS5Controller.hpp"
#include "utils/welcome.hpp"

std::atomic<bool> running(true);

void handle_sigint(int) {
    running = false;
}

int main(int argc, char* argv[]) {
    bool debugMode = false;

    if (argc > 1 && std::string(argv[1]) == "--debug") {
        debugMode = true;
    }

    printWelcomeMessage();
    
    NatsMessagingBus bus("../config/nats.json");
    std::unique_ptr<Controller> controller = std::make_unique<PS5Controller>();
    
    if (!controller->connect()) {
        return 1;
    }
    
    signal(SIGINT, handle_sigint);
    
    while (running) {
        controller->poll();
        bus.publish("CONTROLLER.STATE", controller->getState().dump());
        if (debugMode) Logger::debug("Published controller state: " + controller->getState().dump(4));
        SDL_Delay(10);
    }
    
    SDL_Quit();
    return 0;
}