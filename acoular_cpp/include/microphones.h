#ifndef _MICROPHONES_H_
#define _MICROPHONES_H_

#include <string>
#include <vector>

namespace acoular_cpp
{
// MicGeom class
// 作用：麦克风阵列类，用于描述阵元的位置
/**
 * @brief MicGeom类用于处理麦克风阵列的几何信息
 */
class MicGeom {
public:
    /**
     * @brief 构造函数，从文件中读取麦克风阵列的几何信息
     * @param from_file 包含麦克风阵列几何信息的文件路径
     * @param validate_file 是否验证文件格式，默认为true
     */
    MicGeom(const std::string& from_file, bool validate_file=true);

    /**
     * @brief 析构函数，释放内存
     */
    ~MicGeom();

    /**
     * @brief 获取文件名
     * @return 文件名
     */
    const std::string& get_basename() const;

    /**
     * @brief 获取无效通道的编号
     * @return 无效通道的编号
     */
    const std::vector<int>& get_invalid_channels() const;

    /**
     * @brief 设置无效通道的编号
     * @param invalid_channels 无效通道的编号
     */
    void set_invalid_channels(const std::vector<int>& invalid_channels);

    /**
     * @brief 获取麦克风数量
     * @return 麦克风数量
     */
    int get_num_mics() const;

    /**
     * @brief 获取阵列中心的坐标
     * @return 阵列中心的坐标
     */
    const double* get_center() const;

    /**
     * @brief 获取阵列孔径
     * @return 阵列孔径
     */
    double get_aperture() const;

    /**
     * @brief 获取麦克风位置的坐标
     * @return 麦克风位置的坐标
     */
    const double* get_mpos() const;

private:
    std::string from_file_; ///< 包含麦克风阵列几何信息的文件路径
    bool validate_file_; ///< 是否验证文件格式
    std::string basename_; ///< 文件名
    std::vector<int> invalid_channels_; ///< 无效通道的编号
    int num_mics_; ///< 麦克风数量
    double* center_; ///< 阵列中心的坐标
    double aperture_; ///< 阵列孔径
    double* mpos_; ///< 麦克风位置的坐标

    /**
     * @brief 从文件中导入麦克风位置的坐标
     */
    void import_mpos();
};
} // namespace acoular_cpp
#endif // _MICROPHONES_H_