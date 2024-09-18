#pragma once

#include <mutex>
#include <queue>
#include <string>
#include <functional>
#include <memory>
#include "device.h"

using Command = std::_Mem_fn<std::string(Device::*)()>;
using CommandPtr = std::shared_ptr<Command>;

class CommandQueueItem {
    Command command;
    std::shared_ptr<Device> instance;
public:
    CommandQueueItem(std::shared_ptr<Device> instc, Command cmd) : command(cmd), instance(instc) {}
    std::string doCmd();
};

class CommandQueue {
    std::mutex mtx;
    std::queue<CommandQueueItem> queue;
public:
    void add(std::shared_ptr<Device> instc, CommandPtr cmd);
    void add(const CommandQueueItem& cmd);
    CommandQueueItem take();
    void clear();
    bool queueEmpty();
};
