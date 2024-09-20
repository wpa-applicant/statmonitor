#include "statusMonitor.h"

void StatusMonitor::checkStatusPeriodically2() {
    while(1) {
        cmdQ.add(adc, status, true);
        cmdQ.add(pic, status, true);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// void StatusMonitor::checkStatusPeriodically(std::shared_ptr<Device> dev) {
//     while(1) {
//         cmdQ.add(dev, status);
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }

bool StatusMonitor::doConfig() {
    int configCtr = 0, retriesMid = 4, retriesMax = 10;
    config = adc->config(); // :( // :( // :( // :( // :( //
    while(config.empty()) {
        if(configCtr < retriesMid) {
           std::this_thread::sleep_for(std::chrono::milliseconds(300));
        } else if (configCtr < retriesMax) {
           std::this_thread::sleep_for(std::chrono::milliseconds(600));
        } else {
            std::cout << "No config. Server probably down. Aborting." << std::endl;
            return false;
        }
        config = adc->config();
        configCtr++;

    }
    std::cout << "Connection established" << std::endl;
    return true;
}

void StatusMonitor::deviceSetup(){
    adc = std::make_shared<Device>("adc");
    pic = std::make_shared<Device>("pic");

    if(!doConfig()) { return; }

    status      = std::make_shared<Command>( std::mem_fn(&Device::status));
    reset       = std::make_shared<Command>( std::mem_fn(&Device::reset));
    force_error = std::make_shared<Command>( std::mem_fn(&Device::force_error));

    statusChecker = std::thread(&StatusMonitor::checkStatusPeriodically2, this);
    // adcStatusChecker = std::thread(&StatusMonitor::checkStatusPeriodically, this, adc);
    // picStatusChecker = std::thread(&StatusMonitor::checkStatusPeriodically, this, pic);
    processor = std::thread(&StatusMonitor::processingLoop, this);

    statusChecker.detach();
    // adcStatusChecker.detach();
    // picStatusChecker.detach();
    processor.detach();
}

void StatusMonitor::processingLoop() {
    bool adcDone = false, picDone = false; // :(
    while(1) {
        if(cmdQ.queueEmpty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        CommandQueueItem it = cmdQ.take();

        std::shared_ptr<Device> device;
        bool regularStatusFlag;
        std::string deviceStatus;

        tie(device, regularStatusFlag, deviceStatus) = it.doCmd(); // :(((
        device->devStatus = deviceStatus;

        if(regularStatusFlag) {
            // device->devStatus = deviceStatus;
            if(device == adc) {
                adcDone = true;
            } else if (device == pic) {
                picDone = true;
            } else {
                std::cout << "how did you get here??" << std::endl;
            }

            if(adcDone && picDone) {
                adcDone = picDone = false;
                pic->fsm.iterate();
                adc->fsm.iterate();
            }
        }
    }
}

void StatusMonitor::start() {
    deviceSetup();
}

int main() {
    StatusMonitor statMonitor;
    statMonitor.start();


    while(1) { std::this_thread::sleep_for(std::chrono::seconds(5)); };

    return 0;
}
