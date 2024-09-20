#include "logger.h"

void RingBuffer::save(DebugInfo&& info) {
    data[pos] = std::move(info); // don't swap
    if (++pos == size) {
        pos = 0;
    }
}

void RingBuffer::load() {
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

// CurrentParameters& Logger::readConfig(FILE* f) {
//     // open f
//     // read f
//     // return CurrentConfig(...);  ne moze ni sa std::move()
//     cp = CurrentParameters(1,2,3,4,5);
//     return cp;
// }
