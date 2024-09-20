cmake_minimum_required(VERSION 3.28)
project(statusMonitor)

set(SRC
    "src/device.cpp"
    "src/logger.cpp"
    "src/commandQueue.cpp"
    "src/networkManager.cpp"
    "src/statusMonitor.cpp"
    "src/fsm.cpp"
)

add_executable(statusMonitor "${SRC}")
target_include_directories(statusMonitor PUBLIC "inc")

find_package(CURL REQUIRED)
include_directories(statusMonitor ${CURL_INCLUDE_DIRS})
target_link_libraries(statusMonitor ${CURL_LIBRARIES})

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(statusMonitor nlohmann_json::nlohmann_json)
