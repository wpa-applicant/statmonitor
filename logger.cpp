#include "logger.h"

void RingBuffer::write(DebugInfo&& i) {
    data[pos] = std::move(i);
    if (++pos == size) {
        pos = 0;
    }
}

void RingBuffer::read() {
    for (int i = pos; i < size; ++i) {
        //fprintf  data[i]
    }
    for (int i = 0; i < pos; ++i) {
        //fprintf  data[i]
    }
}

void RingBuffer::clear() {
    data.clear();
    pos = 0;
}

CurrentParameters& Logger::readConfig(FILE* f) {
    // open f
    // read f
    // return CurrentConfig(...);  ne moze ni sa std::move()
}