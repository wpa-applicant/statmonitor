#pragma once
#include <curl/curl.h>
#include <mutex>
#include <iostream>
#include <optional>

class NetworkManager {
//// Thread-safe singleton
private:
    static NetworkManager* instance;
    static std::mutex mtx;
protected:
    NetworkManager() {}
    ~NetworkManager() { instance->deinit(); }
public:
    NetworkManager(NetworkManager &) = delete;
    NetworkManager(const NetworkManager &) = delete;
    static NetworkManager *getInstance();
////
public:
    enum ErrorCode {OK, GLOBAL_INIT_FAILED, EASY_INIT_FAILED};
    std::string GET(const std::string& URL);
    std::string POST(const std::string& URL, const std::string& postMessage = "");
private:
    ErrorCode init();
    void deinit();
    std::string readBuffer;
    CURLcode res;
    CURL *handle;

    static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);
};
