#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "tprocess.h"
#include "spectra.h"

// tools.h
// 作用： 工具函数，用于处理声学信号
namespace acoular_cpp
{

// 作用 : 是从一个SamplesGenerator对象中收集输出并返回一个包含所有数据的数组
// source : SamplesGenerator对象
// nmax : 整数， 从source中收集的最大数据量，如果为-1，则收集所有数据
// num : 整数， 用于定义获取的块的大小
// 返回值 : 一个包含所有数据的数组
std::vector<std::vector<double>> return_result(SamplesGenerator& source, int nmax = -1, int num = 128);

// 作用：计算球形Hankel函数
// n : 整数， 阶数
// z : 复数， 自变量
// derivativearccos : 布尔值， 是否计算arccos的导数
// 返回值： 球形Hankel函数的值
std::complex<double> spherical_hn1(int n, double z, bool derivativearccos=false);

// 作用：是计算麦克风和声源之间的方位角和俯仰角
// direction : 一个包含三个浮点数的数组， 表示声源的方向
// mpos : 一个包含三个浮点数的数组， 表示麦克风的位置
// sourceposition : 一个包含三个浮点数的数组， 表示声源的位置
// 返回值： 一个包含两个浮点数的数组， 表示方位角和俯仰角
std::vector<double> get_radiation_angles(std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition);

// 作用：计算球形波的模式
// lOrder : 整数， 阶数
// direction : 一个包含三个浮点数的数组， 表示声源的方向
// mpos : 一个包含三个浮点数的数组， 表示麦克风的位置
// sourceposition : 一个包含三个浮点数的数组， 表示声源的位置
// 返回值： 一个包含复数的数组， 表示球形波的模式
std::vector<std::complex<double>> get_modes(int lOrder, std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition = {0, 0, 0});

// 作用： sph_harm函数是一个用于计算球谐函数的函数。球谐函数是一组定义在单位球面上的函数，它们在物理学、数学和工程学中具有广泛的应用。在声学中，球谐函数被用来描述声波在空间中的传播和辐射模式
// m : 整数， 阶数
// l : 整数， 阶数
// theta : 浮点数， 极角
// phi : 浮点数， 方位角
// 返回值： 一个复数， 表示球谐函数的值
std::complex<double> sph_harm(int m, int l, double theta, double phi);

// 用于计算频率带的下限和上限
// num : 整数， 频率带的数量
// fmin : 浮点数， 最低频率
// fmax : 浮点数， 最高频率
// 返回值： 一个包含两个浮点数的数组， 表示频率带的下限和上限
std::vector<double> barspectrum(std::vector<double> data, std::vector<double> fftfreqs, int num = 3, bool bar = true, double xoffset = 0.0);

// 用于计算频率带的下限和上限以及相应的值
// data : 一个包含复数的数组， 表示频率响应
// fc : 一个包含浮点数的数组， 表示频率带的中心频率
// bar : 布尔值， 是否计算频率带的下限和上限
// xoffset : 浮点数， x轴的偏移量
// num : 整数， 用于定义获取的块的大小
// masked : 浮点数， 用于表示掩码的值
// 返回值： 一个包含两个浮点数的数组， 表示频率带的下限和上限以及相应的值
std::pair<std::vector<double>, std::vector<double>> bardata(std::vector<double> data, std::vector<double> fc, bool bar = true, double xoffset = 0.0, int num = 3, double masked = -360.0);

} // namespace acoular_cpp
#endif // _TOOLS_H_