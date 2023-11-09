cmake_minimum_required(VERSION 3.20)

project(demo)

# 设置语言标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# 设置构建类型
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

# 设置编译选项
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode")
    set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release mode")
    set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
endif ()

# 设置生成的可执行文件
add_executable(demo main.cpp)