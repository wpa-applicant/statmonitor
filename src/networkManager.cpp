#include "networkManager.h"

NetworkManager* NetworkManager::instance{nullptr};
std::mutex NetworkManager::mtx;

NetworkManager *NetworkManager::getInstance() {
    std::lock_guard<std::mutex> lock(mtx);
    if (instance == nullptr) {
        instance = new NetworkManager();
        instance->init();
    }
    return instance;
}
////

size_t NetworkManager::write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
    ((std::string*)userdata)->append((char*)ptr, size*nmemb);
    return size*nmemb;
}

NetworkManager::ErrorCode NetworkManager::init() {
    if (curl_global_init(CURL_GLOBAL_SSL)) {
        std::cout << "GLOBAL_INIT_FAILED" << std::endl;
        return GLOBAL_INIT_FAILED;
    }
    handle = curl_easy_init();
    if (handle == NULL) {
        std::cout << "EASY_INIT_FAILED" << std::endl;
        return EASY_INIT_FAILED;
    }

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &readBuffer);
    return OK;
}

void NetworkManager::deinit() {
    curl_easy_cleanup(handle);
    curl_global_cleanup();
}

std::string NetworkManager::GET(std::string URL) {
    curl_easy_setopt(handle, CURLOPT_POST, 0);
    readBuffer.clear();
    curl_easy_setopt(handle, CURLOPT_URL, URL.c_str());
    res = curl_easy_perform(handle);
    if (res != CURLE_OK) { std::cerr << "GET failed: " << curl_easy_strerror(res) << std::endl; }  // return something?
    return readBuffer;
}

std::string NetworkManager::POST(std::string URL, std::string postMessage = "") {
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, postMessage.c_str());
    readBuffer.clear();
    curl_easy_setopt(handle, CURLOPT_URL, URL.c_str());
    res = curl_easy_perform(handle);
    if (res != CURLE_OK) { std::cerr << "POST failed: " << curl_easy_strerror(res) << std::endl; }  // return something?
    return readBuffer;
}
