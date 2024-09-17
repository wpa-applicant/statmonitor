#pragma once

#include <mutex>
#include <queue>
#include <string>
#include <functional>
#include <memory>
#include "device.h"

typedef std::_Mem_fn<std::string(Device::*)()> Command;

class CommandQueueItem {
    Command command;
    std::shared_ptr<Device> instance;
public:
    CommandQueueItem(std::shared_ptr<Device> instc, Command cmd) : command(cmd), instance(instc) {}
    std::string doCmd() {
        std::string ret = command(instance);
        return ret;
    }
};

class CommandQueue {
    std::mutex mtx;
    std::queue<CommandQueueItem> queue;
public:
    void add(std::shared_ptr<Device> instc, Command cmd);
    void add(const CommandQueueItem& cmd);
    CommandQueueItem take();
    void clear();
    bool queueEmpty() {
        return queue.empty();
    }
};
