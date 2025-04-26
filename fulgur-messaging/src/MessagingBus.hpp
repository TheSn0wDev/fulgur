#pragma once

#include <string>
#include <functional>

class MessagingBus {
    public:
        virtual ~MessagingBus() = default;
        
        virtual void publish(const std::string& topic, const std::string& message) = 0;
        virtual void subscribe(const std::string& topic, std::function<void(const std::string&)> callback, bool useJetStream = false) = 0;
};