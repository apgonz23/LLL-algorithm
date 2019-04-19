cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

project(LLL)

add_executable(LLL
    main.cpp
    LLL.cpp
)

add_executable(test
    testing.cpp
    LLL.cpp
)
