cmake_minimum_required(VERSION 3.25)
project(os_2_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(os_2_1 main.cpp visualisation.h visualisation.cpp fcfs.h fcfs.cpp miscMultialgFuns.h miscMultialgFuns.cpp sjf.h sjf.cpp fileLoad.cpp fileLoad.h priority.h priority.cpp)
