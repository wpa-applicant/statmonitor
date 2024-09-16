#pragma once
#include <string>
#include <chrono>
#include <vector>

using Clock = std::chrono::system_clock;
static inline std::chrono::time_point<Clock> currTime() {
    return Clock::now();
}

class CurrentParameters {
    std::string kind = "current-parameters";
    std::chrono::time_point<Clock> time;
    int ringBufferSize;
    int picRecoveryTime;
    int picResetTime;
    int adcRecoveryTime;
    int adcResetTime;
public:
    CurrentParameters(int ringBufSz, int picRecT, int picRstT, int adcRecT, int adcRstT)
    : time(currTime()),
      ringBufferSize(ringBufSz), picRecoveryTime(picRecT), picResetTime(picRstT), adcRecoveryTime(adcRecT), adcResetTime(adcRstT)
      {};
};

class Event {
    std::string kind = "event";
    std::chrono::time_point<Clock> time;
    std::string event;
public:
    Event(const std::string& evt) : time(currTime()), event(evt) {}
};

class DebugInfo {
    std::string kind = "debug-info";
    std::chrono::time_point<Clock> time;
    std::string picStatus;
    std::string adcStatus;
public:
    DebugInfo(const std::string& picStat, const std::string& adcStat)
    : time(currTime()), picStatus(picStat), adcStatus(adcStat) {}
    DebugInfo() : DebugInfo("", "") {}
    ~DebugInfo() {}
};

class RingBuffer {
    int size;
    int pos = 0;
    std::vector<DebugInfo> data;    // TODO OVDE PROBLEM
public:
    RingBuffer() : size(40) { data.resize(size); }
    RingBuffer(int sz) : size(sz) { data.resize(sz); }

    void write(DebugInfo&& i);
    void read();
    void clear();
};

class Logger {
    FILE* logFile;
    FILE* configFile; // change type?
    CurrentParameters cp;
    RingBuffer backtrace;

    CurrentParameters& readConfig(FILE* f);
};
