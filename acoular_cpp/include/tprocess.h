#ifndef _TPROCESS_H_
#define _TPROCESS_H_

#include <iostream>
#include <complex>
#include <vector>

namespace acoular_cpp
{

/**
 * @brief 基类 用于生成信号处理块
*/
class SamplesGenerator {
public:
    /**
     * @brief 构造函数 用于生成信号处理块
     * @param sample_freq 浮点数 采样频率
     * @param numchannels 整数 通道数
     * @param numsamples 整数 样本数
    */
    SamplesGenerator(double sample_freq = 1.0, int numchannels = 1, int numsamples = 0) :
        sample_freq(sample_freq), numchannels(numchannels), numsamples(numsamples) {}

    /**
     * @brief 析构函数 释放内存
    */
    virtual ~SamplesGenerator() {}

    /**
     * @brief 生成样本数据
     * @param num 整数 生成的样本数
     * @return 一个包含两个浮点数的数组， 表示频率带的下限和上限
    */
    virtual std::vector<std::vector<double>> result(int num = 128) = 0;

protected:
    double sample_freq; // 采样频率
    int numchannels;    // 通道数
    int numsamples;     // 样本数
};

    
} // namespace acoular_cpp
#endif // _TPROCESS_H_
