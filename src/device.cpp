#include "device.h"

void Device::createURLs() {
    statusURL     = baseURL + name + "/status";
    resetURL      = baseURL + name + "/reset";
    forceErrorURL = baseURL + name + "/force_reset";
}

std::string Device::status() {
    std::string ret = networkMgr->GET(statusURL);
    if (ret == "") {
        std::cout << "ret is empty" << std::endl;
    }
    return ret;
}
int Device::reset() {
    std::string ret = networkMgr->POST(resetURL);
    if (ret != "") {
        std::cout << "ret is " << ret << "." << std::endl;
        return -1;
    }
    return 0;
}

int Device::force_error() {
    std::string ret = networkMgr->POST(forceErrorURL);
    if (ret != "") {
        std::cout << "ret is " << ret << "." << std::endl;
        return -1;
    }
    return 0;
}
