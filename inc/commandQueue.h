#pragma onceE

#include <mutex>
#include <queue>
#include <string>

class CommandQueue {
    std::mutex m;
    std::queue<std::string> q;
    void add(const std::string& s);
    std::string take();
    void clear();
};
