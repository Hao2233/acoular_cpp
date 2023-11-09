#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

#include "tools.h"

// 主要是一些c++的测试
int main(int argc, char const *argv[])
{
    // 测试C++版本
    std::cout << "C++ version: " << __cplusplus << std::endl;

    // vector
    std::vector<int> vec_temp(10,2);
    std::cout << "vector size is " << vec_temp.size() << std::endl;
    std::cout << "vector 3 is  " << vec_temp[2] << std::endl;

    // tools 测试

    return 0;
}
