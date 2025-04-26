#include <memory>
#include <thread>
#include <chrono>
#include <iostream>
#include <csignal>
#include <atomic>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include "NatsMessagingBus.hpp"
#include "controller/PS5Controller.hpp"
#include "utils/welcome.hpp"

std::atomic<bool> running(true);

void handle_sigint(int) {
    running = false;
}

int main() {
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
        std::cout << controller->getState().dump(4);
        SDL_Delay(10);
    }
    
    SDL_Quit();
    return 0;
}