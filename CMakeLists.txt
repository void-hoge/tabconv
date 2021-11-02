cmake_minimum_required(VERSION 3.8)
project(tabconv CXX)
add_executable(tabconv main.cpp utility.cpp)
set(CMAKE_CXX_FLAGS "-std=c++17 -O2 -mtune=native -march=native -flto -pthread -Wall")
