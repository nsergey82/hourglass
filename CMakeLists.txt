cmake_minimum_required(VERSION 3.12)
project(hourglass)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(library)

include_directories(library/include)

add_executable(hourglass app/main.cpp)

target_link_libraries(hourglass PRIVATE hgapi)
