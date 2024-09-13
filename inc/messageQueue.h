#pragma once

#include <mutex>
#include <queue>
#include <string>

class MessageQueue {
    std::mutex m;
    std::queue<std::string> q;
    void add(const std::string& s);
    std::string take();
    void clear();
};
