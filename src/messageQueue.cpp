#include "messageQueue.h"

void MessageQueue::add(const std::string& s) {
    std::lock_guard<std::mutex> l(m);
    q.push(s);
}
std::string MessageQueue::take() {
    std::lock_guard<std::mutex> l(m);
    std::string ret = q.front();
    q.pop();
    return ret;
}
void MessageQueue::clear() {
    std::lock_guard<std::mutex> l(m);
    while(!q.empty()) {
        (void)q.pop();
    }
}
