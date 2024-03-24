cmake_minimum_required(VERSION 3.22)
project(crow_barcode)

include_directories(include)
add_executable(demo main.cpp)

# crow
# find_package(Crow)
# target_link_libraries(your_project PUBLIC Crow::Crow)