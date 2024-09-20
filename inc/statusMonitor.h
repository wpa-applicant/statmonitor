#pragma once
#include "commandQueue.h"
// #include "logger.h"
#include <thread>
#include <nlohmann/json.hpp>

class StatusMonitor {
    CommandQueue cmdQ;
    // Logger logger;
    void deviceSetup();
    bool doConfig();
    void processingLoop();

    std::thread processor;

    void checkStatusPeriodically2();
    // void checkStatusPeriodically(std::shared_ptr<Device> dev);

    CommandPtr status;
    CommandPtr reset;
    CommandPtr force_error;

    std::shared_ptr<Device> adc;
    std::shared_ptr<Device> pic;

    std::string config;

    std::thread statusChecker;
    // std::thread adcStatusChecker;
    // std::thread picStatusChecker;
public:
    void start();
};
