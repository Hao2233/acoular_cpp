cmake_minimum_required(VERSION 3.20)

project(acoular_cpp)

# 设置语言标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# 设置强制检查标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置构建类型呢
set(CMAKE_BUILD_TYPE "Debug")
#set (CMAKE_BUILD_TYPE "Release")

# 判断构建类型
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
    set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g -ggdb")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release mode")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
    set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")
endif ()

# 设置头文件目录
include_directories(${PROJECT_SOURCE_DIR}/acoular_cpp/include)