#include "device.h"
/*
 * Create URLs once for each new device
 */
void Device::createURLs() {
    statusURL     = baseURL + name + "/status";
    resetURL      = baseURL + name + "/reset";
    forceErrorURL = baseURL + name + "/force_error";
}

/*
 * ret contains the result of GET (which will be status)
 */
std::string Device::status() {
    std::string ret = networkMgr->GET(statusURL);
    if (ret == "") {
        std::cout << "Warning: networkManager returned nothing" << std::endl;
    }
    return ret;
}

/*
 * ret contains the result of POST (which will be status)
 */
std::string Device::reset() {
    std::string ret = networkMgr->POST(resetURL);
    if (ret == "") {
        std::cout << "Warning: networkManager returned nothing" << std::endl;
    }
    return ret;
}

/*
 * ret contains the result of POST (which will be status)
 */
std::string Device::force_error() {
    std::string ret = networkMgr->POST(forceErrorURL);
    if (ret == "") {
        std::cout << "Warning: networkManager returned nothing" << std::endl;
    }
    return ret;
}
