#include "statusMonitor.h"
#include "commandQueue.h"

int main() {
    CommandQueue cmdQ;

    std::shared_ptr<Device> adc = std::make_shared<Device>("adc");
    std::shared_ptr<Device> pic = std::make_shared<Device>("pic");

    Command status = std::mem_fn(&Device::status);
    Command reset = std::mem_fn(&Device::reset);
    Command force_error = std::mem_fn(&Device::force_error);

    // std::string (Device::* deviceStatus)() = &Device::status;



    std::cout << status(*adc) << std::endl;
    std::cout << status(*pic) << std::endl;




    cmdQ.add(adc, status);
    cmdQ.add(adc, status);
    cmdQ.add(adc, status);
    cmdQ.add(adc, status);
    cmdQ.add(pic, status);
    cmdQ.add(adc, status);
    cmdQ.add(adc, reset);
    cmdQ.add(adc, status);
    cmdQ.add(adc, status);
    cmdQ.add(adc, status);
    cmdQ.add(pic, reset);
    cmdQ.add(adc, status);
    cmdQ.add(pic, status);
    cmdQ.add(adc, status);
    cmdQ.add(adc, force_error);
    cmdQ.add(pic, status);
    cmdQ.add(adc, status);
    cmdQ.add(adc, status);
    cmdQ.add(pic, reset);
    cmdQ.add(adc, status);
    cmdQ.add(pic, status);
    cmdQ.add(adc, reset);
    cmdQ.add(pic, status);
    cmdQ.add(adc, status);


    while(!cmdQ.queueEmpty()) {
        CommandQueueItem it = cmdQ.take();
        std::string res = it.doCmd();
        std::cout << res << std::endl;
    }


    return 0;
}