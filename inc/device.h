#pragma once
#include "networkManager.h"
#include "fsm.h"
#include <map>
/*
 * Class for communicating to simple devices, or base class for more complex ones.
 */
class Device {
protected:
    NetworkManager *networkMgr;
    std::string name;
    std::string baseURL;
    void createURLs();
public:
    StatusStateMachine fsm;
    std::string devOldStatus;
    std::string devStatus;
    std::string config();
    std::string status();
    std::string reset();
    std::string force_error();
    Device(std::string name, std::string url) : name(name), baseURL(url), networkMgr(NetworkManager::getInstance())
    {
        createURLs();
    }
    Device(std::string name) : Device(name, "http://localhost:3000/") {}

    ~Device() {};
protected:
    std::string statusURL;
    std::string resetURL;
    std::string forceErrorURL;
};