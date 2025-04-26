#pragma once

#include "MessagingBus.hpp"
#include <nlohmann/json.hpp>
#include <nats/nats.h>
#include <string>
#include <functional>

class NatsMessagingBus : public MessagingBus {
    public:
        NatsMessagingBus(const std::string& configPath);
        ~NatsMessagingBus() override;
        
        void publish(const std::string& topic, const std::string& message) override;
        void subscribe(const std::string& topic, std::function<void(const std::string&)> callback, bool useJetStream = false) override;
    
    private:
        natsConnection* conn = nullptr;
        natsOptions* opts = nullptr;
        std::string serverUrl;
        
        void loadConfig(const std::string& configPath);
};