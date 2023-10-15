#ifndef _CALIB_H_
#define _CALIB_H_

#include <string>
#include <vector>

namespace acoular_cpp
{
// 校准数据类
// 作用：从文件中读取校准数据
class Calib {
public:
    // 构造函数，从文件中读取数据
    Calib(const std::string& from_file);
    // 获取文件名
    std::string get_basename() const;
    // 获取麦克风数量
    int get_num_mics() const;
    // 获取校准数据
    std::vector<double> get_data() const;

private:
    std::string from_file; // 数据文件路径
    std::string basename; // 文件名
    int num_mics; // 麦克风数量
    std::vector<double> data; // 校准数据
    // 从文件中导入数据，这里读取的是xml文件
    void import_data();
};

} // namespace acoular_cpp
#endif // _CALIB_H_