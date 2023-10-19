#ifndef _SPECTRA_H_
#define _SPECTRA_H_

#include <cmath>
#include <vector>

namespace acoular_cpp
{

/**
 * @brief 用于计算频率带的合成频率值
 * @param data 一个包含复数的数组， 表示频率响应
 * @param freqs 一个包含浮点数的数组， 表示频率值
 * @param f 一个包含浮点数的数组， 表示频率带的合成频率值
 * @param num 整数， 用于定义获取的块的大小
 * @return 一个包含复数的数组， 表示频率带的合成频率值
*/
std::vector<double> synthetic(std::vector<double> data, std::vector<double> freqs, std::vector<double> f, int num = 3);
    
} // namespace acoular_cpp
#endif // _SPECTRA_H_