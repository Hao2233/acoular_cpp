cmake_minimum_required(VERSION 3.20)

project(demo)

# 设置语言标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# 设置构建类型
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

# 判断构建类型
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode")
    # 设置编译选项
    add_compile_options(-g)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release mode")
    # 设置编译选项
    add_compile_options(-O3)
endif ()

# 设置生成的可执行文件
add_executable(demo main.cpp)