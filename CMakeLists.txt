cmake_minimum_required(VERSION 3.28)
project(statusMonitor)

set(SRC
    "src/device.cpp"
    "src/logger.cpp"
    "src/messageQueue.cpp"
    "src/networkManager.cpp"
    "src/statusMonitor.cpp"
)

add_executable(statusMonitor "${SRC}")
target_include_directories(statusMonitor PUBLIC "inc")

find_package(CURL REQUIRED)
include_directories(statusMonitor ${CURL_INCLUDE_DIRS})
target_link_libraries(statusMonitor ${CURL_LIBRARIES})