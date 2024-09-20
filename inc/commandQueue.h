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
protected:
    Command command;
    std::shared_ptr<Device> instance;
    bool regularStatusCheckFlag; // :(
public:
    CommandQueueItem(std::shared_ptr<Device> instc, Command cmd, bool rStatFlag) : command(cmd), instance(instc), regularStatusCheckFlag(rStatFlag) {}
    CommandQueueItem(std::shared_ptr<Device> instc, Command cmd) : CommandQueueItem(instc, cmd, false) {}
    std::tuple<std::shared_ptr<Device>, bool, std::string> doCmd();
};

class CommandQueue {
    std::mutex mtx;
    std::queue<CommandQueueItem> queue;
public:
    void add(std::shared_ptr<Device> instc, CommandPtr cmd, bool rStatFlag=false);
    void add(const CommandQueueItem& cmd);
    CommandQueueItem take();
    void clear();
    bool queueEmpty();
};
