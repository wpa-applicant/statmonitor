#include "commandQueue.h"

void CommandQueue::add(const std::string& s) {
    std::lock_guard<std::mutex> l(m);
    q.push(s);
}
std::string CommandQueue::take() {
    std::lock_guard<std::mutex> l(m);
    std::string ret = q.front();
    q.pop();
    return ret;
}
void CommandQueue::clear() {
    std::lock_guard<std::mutex> l(m);
    while(!q.empty()) {
        (void)q.pop();
    }
}
