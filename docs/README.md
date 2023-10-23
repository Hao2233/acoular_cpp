# 文档说明

目前为止，项目的文档就是这个样子，后续会写的更加详细

可能会存在一些不完善的地方，欢迎指正

当前目录是文档目录，用于存放项目文档。

## 文档目录结构

```
docs
├── README.md
├── Calib.md

```

## example

python_example 目录主要存放一些python的使用示例，用于检测c++实现的代码是否正确


## 补充说明

1. 目前程序使用的浮点类型是double
2. 矩阵使用c++标准库的vector，将来会增加矩阵库的类
3. 复数类型使用的是c++的complex类型
4. 目前的矩阵类型是c++vector，矩阵的操作等使用Eigen库


## 关于Eigen库

1. 简介

Eigen库是一个开源的模版库，支持线性代数的运算，包括矩阵运算，矩阵分解，矩阵求逆，矩阵求特征值等等，是一个非常强大的线性代数库，而且使用非常方便，只需要包含头文件就可以使用，不需要编译，不需要安装，非常方便。

2. 编译和安装

官网：http://eigen.tuxfamily.org/index.php?title=Main_Page

```bash
# 解压
tar -xvjf eigen-3.4.0.tar.bz2 

# 进入解压后的目录
cd eigen-3.4.0

# 创建build目录
mkdir build

# 进入build目录
cd build

# 编译安装到指定目录
cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/install

# 安装
make install

```

3. 使用

这里只给出CMake的使用方法，其他的使用方法可以参考官网

```cmake
# CMake最小版本
cmake_minimum_required(VERSION 3.20)

# 项目名称
project(eigen_demo)

# 设置语言标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 设置强制检查语法
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)

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

# 设置Eigen库路径变量
set(EIGEN3_INCLUDE_DIR /usr/local/include/eigen3)
# 设置Eigne库头文件
set(EIGEN3_INCLUDE_DIR ${EIGEN3_INCLUDE_DIR} CACHE PATH "Eigen include directory")
# 设置Eigne库库文件
set(EIGEN3_LIBRARY_DIR ${EIGEN3_LIBRARY_DIR} CACHE PATH "Eigen library directory")

# 设置头文件路径
include_directories(${EIGEN3_INCLUDE_DIR}/include)

# 设置源文件路径
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_DIR ${PROJECT_SOURCE_DIR})

# 设置打印信息
# 输出构建类型
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# 输出Eigen库路径
message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")

# 判断Eigen库是否加载成功
if (EIGEN3_INCLUDE_DIR)
    message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
endif()

# 设置生成可执行文件
add_executable(eigen_demo ${SRC_DIR}/main.cpp)
```
