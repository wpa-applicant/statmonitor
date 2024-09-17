#include "commandQueue.h"

void CommandQueue::add(std::shared_ptr<Device> instc, Command cmd) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.emplace(CommandQueueItem(instc, cmd));
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
