#include "configuration.h"

#include <iostream>

int main() {
    acoular_cpp::Config config;

    // 设置全局缓存模式为覆盖缓存
    config.set_global_caching(acoular_cpp::Config::OVERWRITE);

    // 设置HDF5库为PyTables库
    config.set_h5library(acoular_cpp::Config::PYTABLES);

    // 设置缓存目录
    config.set_cache_dir("/Users/zhanghao/code/cpp/acoular_cpp/examples/class_examples/configuration");

    // 设置时间数据目录
    config.set_td_dir("/Users/zhanghao/code/cpp/acoular_cpp/examples/class_examples/configuration");

    // 设置是否使用TraitsUI
    config.set_use_traitsui(true);

    // 获取全局缓存模式
    acoular_cpp::Config::GlobalCaching global_caching = config.global_caching();

    // 获取HDF5库
    acoular_cpp::Config::H5Library h5library = config.h5library();

    // 获取缓存目录
    std::string cache_dir = config.cache_dir();

    // 获取时间数据目录
    std::string td_dir = config.td_dir();

    // 获取是否使用TraitsUI
    bool use_traitsui = config.use_traitsui();

    return 0;
}
