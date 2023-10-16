#include "grids.h"

#include <iostream>
#include <vector>


// class Polygon demo
int main(int argc, char const *argv[])
{
    // 创建一个三角形
    std::vector<double> x = {0, 1, 1};
    std::vector<double> y = {0, 0, 1};
    acoular_cpp::Polygon poly(x, y);

    // 判断点是否在三角形内部
    double xpoint = 0.5;
    double ypoint = 0.5;
    double smalld = 1e-12;
    double is_inside = poly.is_inside(xpoint, ypoint, smalld);

    // 输出结果
    if (is_inside)
    {
        std::cout << "点在多边形内部" << std::endl;
    }
    else
    {
        std::cout << "点在多边形外部" << std::endl;

    }

    return 0;
}
