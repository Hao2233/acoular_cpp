#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace acoular_cpp
{
/**
 * @brief 配置类，用于管理全局缓存、HDF5库、缓存目录、时间数据目录和TraitsUI的使用。
 */
class Config
{
public:
    /**
     * @brief 全局缓存模式枚举。
     */
    enum GlobalCaching
    {
        INDIVIDUAL, /**< 每个对象单独缓存 */
        ALL,        /**< 所有对象共享缓存 */
        NONE,       /**< 不使用缓存 */
        READONLY,   /**< 只读缓存 */
        OVERWRITE   /**< 覆盖缓存 */
    };

    /**
     * @brief HDF5库枚举。
     */
    enum H5Library
    {
        PYTABLES, /**< PyTables库 */
        H5PY      /**< h5py库 */
    };

    /**
     * @brief 构造函数。
     */
    Config();

    /**
     * @brief 获取全局缓存模式。
     * @return 全局缓存模式。
     */
    GlobalCaching global_caching() const;

    /**
     * @brief 设置全局缓存模式。
     * @param global_caching 全局缓存模式。
     */
    void set_global_caching(GlobalCaching global_caching);

    /**
     * @brief 获取HDF5库。
     * @return HDF5库。
     */
    H5Library h5library() const;

    /**
     * @brief 设置HDF5库。
     * @param h5library HDF5库。
     */
    void set_h5library(H5Library h5library);

    /**
     * @brief 获取缓存目录。
     * @return 缓存目录。
     */
    std::string cache_dir() const;

    /**
     * @brief 设置缓存目录。
     * @param cache_dir 缓存目录。
     */
    void set_cache_dir(const std::string &cache_dir);

    /**
     * @brief 获取时间数据目录。
     * @return 时间数据目录。
     */
    std::string td_dir() const;

    /**
     * @brief 设置时间数据目录。
     * @param td_dir 时间数据目录。
     */
    void set_td_dir(const std::string &td_dir);

    /**
     * @brief 获取是否使用TraitsUI。
     * @return 是否使用TraitsUI。
     */
    bool use_traitsui() const;

    /**
     * @brief 设置是否使用TraitsUI。
     * @param use_traitsui 是否使用TraitsUI。
     */
    void set_use_traitsui(bool use_traitsui);

private:
    GlobalCaching _global_caching; /**< 全局缓存模式 */
    H5Library _h5library;          /**< HDF5库 */
    std::string _cache_dir;        /**< 缓存目录 */
    std::string _td_dir;           /**< 时间数据目录 */
    bool _use_traitsui;            /**< 是否使用TraitsUI */

    /**
     * @brief 检查HDF5库是否可用。
     */
    void _assert_h5library();
};
} // namespace acoular_cpp
#endif // _CONFIGURATION_H_