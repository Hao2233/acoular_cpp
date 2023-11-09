#ifndef _TOOLS_H_
#define _TOOLS_H_

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

#include "tprocess.h"
#include "spectra.h"

/**
 * @brief 工具函数，用于处理声学信号
*/
namespace acoular_cpp
{

/**
 * @brief 是从一个SamplesGenerator对象中收集输出并返回一个包含所有数据的数组
 * @param source SamplesGenerator对象
 * @param nmax 整数，从source中收集的最大数据量，如果为-1，则收集所有数据
 * @return 一个包含所有数据的数组
*/
std::vector<std::vector<double>> return_result(SamplesGenerator& source, int nmax = -1, int num = 128);

/**
 * @brief 计算球形Hankel函数
 * @param n 整数，阶数
 * @param z 复数，自变量
 * @param derivativearccos 布尔值，是否计算arccos的导数
 * @return 球形Hankel函数的值
*/
std::complex<double> spherical_hn1(int n, double z, bool derivativearccos=false);

/**
 * @brief 是计算麦克风和声源之间的方位角和俯仰角
 * @param direction 一个包含三个浮点数的数组，表示声源的方向
 * @param mpos 一个包含三个浮点数的数组，表示麦克风的位置
 * @param sourceposition 一个包含三个浮点数的数组，表示声源的位置
 * @return 一个包含两个浮点数的数组， 表示方位角和俯仰角
*/
std::vector<double> get_radiation_angles(std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition);

/**
 * @brief 计算球形波的模式
 * @param lOrder 整数，阶数
 * @param direction 一个包含三个浮点数的数组，表示声源的方向
 * @param mpos 一个包含三个浮点数的数组，表示麦克风的位置
 * @param sourceposition 一个包含三个浮点数的数组，表示声源的位置
 * @return 一个包含复数的数组， 表示球形波的模式
*/
std::vector<std::complex<double>> get_modes(int lOrder, std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition = {0, 0, 0});

/**
 * @brief sph_harm函数是一个用于计算球谐函数的函数。球谐函数是一组定义在单位球面上的函数，在声学中，球谐函数被用来描述声波在空间中的传播和辐射模式
 * @param m 整数 阶数
 * @param l 整数 阶数
 * @param theta 浮点数 极角
 * @param phi 浮点数 方位角
 * @return 一个复数， 表示球谐函数的值
*/
std::complex<double> sph_harm(int m, int l, double theta, double phi);

/**
 * @brief 用于计算频率带的下限和上限
 * @param num 整数 频率带的数量
 * @param fmin 浮点数 最低频率
 * @param fmax 浮点数 最高频率
 * @return 一个包含两个浮点数的数组， 表示频率带的下限和上限
*/
std::vector<double> barspectrum(std::vector<double> data, std::vector<double> fftfreqs, int num = 3, bool bar = true, double xoffset = 0.0);

/**
 * @brief 用于计算频率带的下限和上限以及相应的值
 * @param data 一个包含复数的数组 表示频率响应
 * @param fc 一个包含浮点数的数组 表示频率带的中心频率
 * @param bar 布尔值 是否计算频率带的下限和上限
 * @param xoffset 浮点数 x轴的偏移量
 * @param num 整数 用于定义获取的块的大小
 * @param masked 浮点数 用于表示掩码的值
 * @return 一个包含两个浮点数的数组， 表示频率带的下限和上限以及相应的值
*/
std::pair<std::vector<double>, std::vector<double>> bardata(std::vector<double> data, std::vector<double> fc, bool bar = true, double xoffset = 0.0, int num = 3, double masked = -360.0);

/**
 * @brief 将一维矩阵写入文件
 * 
 * @param data 一维矩阵
 * @param filename 文件名
 * @return int 返回码
 */
int to_file(const std::vector<double> &data, const std::string &filename);

/**
 * @brief 将二维矩阵写入文件
 * 
 * @param data 二维矩阵
 * @param filename 文件名
 * @return int 返回码
 */
int to_file(const std::vector<std::vector<double>> &data, const std::string &filename);

} // namespace acoular_cpp
#endif // _TOOLS_H_