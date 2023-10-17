#ifndef _TPROCESS_H_
#define _TPROCESS_H_

#include <iostream>
#include <complex>
#include <vector>

namespace acoular_cpp
{

// SamplesGenerator class
// 基类
class SamplesGenerator {
public:
    // 构造函数
    // sample_freq : 浮点数， 采样频率
    // numchannels : 整数， 通道数
    // numsamples : 整数， 样本数
    SamplesGenerator(double sample_freq = 1.0, int numchannels = 1, int numsamples = 0) :
        sample_freq(sample_freq), numchannels(numchannels), numsamples(numsamples) {}

    // 析构函数 虚函数
    // 作用： 释放内存
    virtual ~SamplesGenerator() {}

    // 作用： 生成样本数据
    // num：整数， 生成的样本数
    // 返回值： 一个包含两个浮点数的数组， 表示频率带的下限和上限
    virtual std::vector<std::vector<double>> result(int num = 128) = 0;

protected:
    double sample_freq; // 采样频率
    int numchannels;    // 通道数
    int numsamples;     // 样本数
};

    
} // namespace acoular_cpp
#endif // _TPROCESS_H_
