#include "statusMonitor.h"

void StatusMonitor::checkStatusPeriodically(std::shared_ptr<Device> dev) {
    while(1) {
        cmdQ.add(dev, status);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void StatusMonitor::deviceSetup(){
    adc = std::make_shared<Device>("adc");
    pic = std::make_shared<Device>("pic");

    status      = std::make_shared<Command>( std::mem_fn(&Device::status));
    reset       = std::make_shared<Command>( std::mem_fn(&Device::reset));
    force_error = std::make_shared<Command>( std::mem_fn(&Device::force_error));

    adcStatusChecker = std::thread(&StatusMonitor::checkStatusPeriodically, this, adc);
    picStatusChecker = std::thread(&StatusMonitor::checkStatusPeriodically, this, pic);

    adcStatusChecker.detach();
    picStatusChecker.detach();
}


void StatusMonitor::processingLoop() {
    while(1) {
        if(cmdQ.queueEmpty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        CommandQueueItem it = cmdQ.take();
        std::string res = it.doCmd();
        std::cout << ": " << res << std::endl;
    }
}

void StatusMonitor::start() {
    deviceSetup();
    processingLoop();
}

int main() {
    StatusMonitor statMonitor;
    statMonitor.start();

    return 0;
}
