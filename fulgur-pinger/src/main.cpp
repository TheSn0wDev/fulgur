#include <iostream>
#include <chrono>
#include <csignal>
#include <thread>
#include <string>
#include <regex>
#include "Logger.hpp"
#include "NatsMessagingBus.hpp"

bool keepRunning = true;

void signalHandler(int signum) {
    Logger::info("Interruption signal received. Exiting...");
    keepRunning = false;
}

int getLatency(const std::string& target) {
    std::string cmd = "ping -c 1 " + target;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        Logger::error("Failed to run ping command.");
        return -1;
    }

    char buffer[256];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }

    pclose(pipe);

    std::regex timeRegex(R"(time=([\d\.]+)\s*ms)");
    std::smatch match;
    if (std::regex_search(output, match, timeRegex)) {
        float latency = std::stof(match[1]);
        Logger::debug("[" + target + "] " + match[1].str() + " ms");
        return static_cast<int>(latency);
    } else {
        Logger::error("No latency data found for " + target);
        return -1;
    }
}

int main() {
    std::string target = "fulgur.local";
    NatsMessagingBus bus("../config/nats.json");

    signal(SIGINT, signalHandler); 

    while (keepRunning) {
        int latency = getLatency(target); 
        bus.publish("FULGUR.INFOS", "{\"latency\": " + std::to_string(latency) + "}");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}