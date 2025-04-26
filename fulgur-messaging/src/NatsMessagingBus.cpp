#include "NatsMessagingBus.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

NatsMessagingBus::NatsMessagingBus(const std::string& configPath) {
    loadConfig(configPath);
    
    natsOptions_Create(&opts);
    natsOptions_SetURL(opts, serverUrl.c_str());
    
    if (natsConnection_Connect(&conn, opts) != NATS_OK) {
        std::cerr << "Failed to connect to NATS server." << std::endl;
    }
}

NatsMessagingBus::~NatsMessagingBus() {
    natsConnection_Destroy(conn);
    natsOptions_Destroy(opts);
}

void NatsMessagingBus::publish(const std::string& topic, const std::string& message) {
    natsConnection_Publish(conn, topic.c_str(), message.c_str(), message.size());
}

void NatsMessagingBus::subscribe(const std::string& topic, std::function<void(const std::string&)> callback, bool useJetStream) {
    if (useJetStream) {
        std::cerr << "JetStream subscription not implemented yet." << std::endl;
        return;
    }
    
    auto handler = [](natsConnection* nc, natsSubscription* sub, natsMsg* msg, void* closure) {
        auto* cb = static_cast<std::function<void(const std::string&)>*>(closure);
        (*cb)(std::string(natsMsg_GetData(msg), natsMsg_GetDataLength(msg)));
        natsMsg_Destroy(msg);
    };
    
    natsSubscription* sub = nullptr;
    natsConnection_Subscribe(&sub, conn, topic.c_str(), handler, &callback);
}

void NatsMessagingBus::loadConfig(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Could not open config file." << std::endl;
        return;
    }
    
    json configJson;
    file >> configJson;
    
    serverUrl = configJson.value("nats_url", "nats://localhost:4222");
}