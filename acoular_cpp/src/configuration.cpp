#include "configuration.h"

namespace acoular_cpp
{
Config::Config() {
    _assert_h5library();
}

Config::GlobalCaching Config::global_caching() const {
    return _global_caching;
}

void Config::set_global_caching(GlobalCaching global_caching) {
    _global_caching = global_caching;
}

Config::H5Library Config::h5library() const {
    return _h5library;
}

void Config::set_h5library(H5Library h5library) {
    _h5library = h5library;
}

std::string Config::cache_dir() const {
    std::string cache_dir;
    if (_cache_dir.empty()) {
        cache_dir = fs::current_path().string() + "/cache";
        if (!fs::exists(cache_dir)) {
            fs::create_directory(cache_dir);
        }
        cache_dir = _cache_dir;

        // 源码 没搞清楚这里为什么这样写，报错
        // _cache_dir = cache_dir
    }
    return cache_dir;
}

void Config::set_cache_dir(const std::string& cache_dir) {
    if (!fs::exists(cache_dir)) {
        fs::create_directory(cache_dir);
    }
    _cache_dir = cache_dir;
}

std::string Config::td_dir() const {
    return _td_dir;
}

void Config::set_td_dir(const std::string& td_dir) {
    _td_dir = td_dir;
}

bool Config::use_traitsui() const {
    return _use_traitsui;
}

void Config::set_use_traitsui(bool use_traitsui) {
    if (use_traitsui) {
        // python 源代码中有这一行，但是我不知道这是什么意思
        // If user tries to use traitsuis and it's not installed, this will throw an error.
    }
    _use_traitsui = use_traitsui;
}

void Config::_assert_h5library()
{
    // python 中说查看HDF5库是否引入
}

}