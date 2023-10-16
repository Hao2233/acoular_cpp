cmake_minimum_required(VERSION 3.20)

project(grids_demo)

# 设置语言标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# 设置强制检查语法标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置构建类型
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")

# 设置构建类型
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
    set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g -ggdb")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release mode")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
    set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")
endif ()

# 设置头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ../../../acoular_cpp/include
)

# 源文件路径
set(SRC_LIST 
    main.cpp
    ../../../acoular_cpp/src/grids.cpp
)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST})