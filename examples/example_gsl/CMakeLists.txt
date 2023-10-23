cmake_minimum_required(VERSION 3.20)

# 项目名称
project(gsl_demo)

# 设置语言标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 设置强制检查语法
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

# 设置构建类型
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

# 设置编译选项
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")
endif()

# 设置GSL库的路径
set(CMAKE_PREFIX_PATH 
    "/Users/zhanghao/code/SDK/gsl" ${CMAKE_PREFIX_PATH}
)

# 设置GSL库包
find_package(GSL REQUIRED)

# 设置源文件路径
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_DIR ${PROJECT_SOURCE_DIR})

# 设置打印信息
# 输出构建类型
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# 判断GSL库是否存在
if (GSL_FOUND)
    message(STATUS "GSL_INCLUDE_DIRS: ${GSL_INCLUDE_DIRS}")
    message(STATUS "GSL_LIBRARIES: ${GSL_LIBRARIES}")
    message(STATUS "GSL_VERSION: ${GSL_VERSION}")
else()
    message(FATAL_ERROR "GSL library not found")
endif()

# 设置生成可执行文件
add_executable(gsl_demo ${SRC_DIR}/main.cpp)

# 设置GSL链接库
target_link_libraries(gsl_demo GSL::gsl GSL::gslcblas)