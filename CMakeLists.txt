cmake_minimum_required(VERSION 3.22)
project(crow_barcode CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include_directories(include)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_INCLUDE_DIRS})
find_package(ZBar REQUIRED)

add_executable(demo main.cpp)
# add_executable(demo demo.cpp)

target_include_directories(demo
    PUBLIC
        ${OpenCV_INCLUDE_DIRS}
        ${ZBar_INCLUDE_DIRS}
        "include"
)

target_link_libraries(demo
    PUBLIC
        ${OpenCV_LIBS} 
        ${ZBAR_LIBRARIES}
)
# crow
# find_package(Crow)
# target_link_libraries(your_project PUBLIC Crow::Crow)