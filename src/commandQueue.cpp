#include "commandQueue.h"

std::tuple<std::shared_ptr<Device>, bool, std::string> CommandQueueItem::doCmd() {
    return std::make_tuple(instance, regularStatusCheckFlag, command(instance));
}

void CommandQueue::add(std::shared_ptr<Device> instc, CommandPtr cmd, bool rStatFlag) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.emplace(CommandQueueItem(instc, *cmd, rStatFlag));
}

void CommandQueue::add(const CommandQueueItem& c) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.push(c);
}

CommandQueueItem CommandQueue::take() {
    std::lock_guard<std::mutex> lock(mtx);
    CommandQueueItem ret = std::move(queue.front());
    queue.pop();
    return ret;
}

void CommandQueue::clear() {
    std::lock_guard<std::mutex> lock(mtx);
    while(!queue.empty()) {
        (void)queue.pop();
    }
}

bool CommandQueue::queueEmpty() {
    return queue.empty();
}
