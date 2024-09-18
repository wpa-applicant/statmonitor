#pragma once
#include "commandQueue.h"
#include <thread>

class StatusMonitor {
    CommandQueue cmdQ;
    void deviceSetup();
    void processingLoop();

    void checkStatusPeriodically(std::shared_ptr<Device> dev);

    CommandPtr status;
    CommandPtr reset;
    CommandPtr force_error;

    std::shared_ptr<Device> adc;
    std::shared_ptr<Device> pic;

    std::thread adcStatusChecker;
    std::thread picStatusChecker;
public:
    void start();
};
