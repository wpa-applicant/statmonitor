#include "device.h"
/*
 * Create URLs once for each new device
 */
void Device::createURLs() {
    statusURL     = baseURL + name + "/status";
    resetURL      = baseURL + name + "/reset";
    forceErrorURL = baseURL + name + "/force_reset";
}

/*
 * ret contains the result of GET
 */
std::string Device::status() {
    std::cout << statusURL << std::endl;
    std::string ret = networkMgr->GET(statusURL);
    if (ret == "") {
        std::cout << "ret is empty" << std::endl;
    }
    return ret;
}

/*
 * ret contains the result of POST. This should be empty in normal circumstances
 */
std::string Device::reset() {
    std::cout << resetURL << std::endl;
    std::string ret = networkMgr->POST(resetURL);
    if (ret != "") {
        std::cout << "ret is " << ret << "." << std::endl;
        // return -1;
    }
    return ret;
}

/*
 * ret contains the result of POST. This should be empty in normal circumstances
 */
std::string Device::force_error() {
    std::cout << forceErrorURL << std::endl;
    std::string ret = networkMgr->POST(forceErrorURL);
    if (ret != "") {
        std::cout << "ret is " << ret << "." << std::endl;
        // return -1;
    }
    return ret;
}
