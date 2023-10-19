#include "microphones.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace acoular_cpp
{

MicGeom::MicGeom(const std::string &from_file, bool validate_file)
    : from_file_(from_file), validate_file_(validate_file), num_mics_(0), center_(nullptr), aperture_(0.0), mpos_(nullptr)
{
    // 从文件中读取麦克风阵列的几何信息
    std::ifstream file(from_file_);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + from_file_);
    }

    // 读取文件名
    size_t pos = from_file_.find_last_of("/\\");
    if (pos != std::string::npos)
    {
        basename_ = from_file_.substr(pos + 1);
    }
    else
    {
        basename_ = from_file_;
    }

    // 读取阵列中心的坐标和孔径
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    iss >> center_[0] >> center_[1] >> center_[2] >> aperture_;

    // 读取麦克风数量
    std::getline(file, line);
    iss.clear();
    iss.str(line);
    iss >> num_mics_;

    // 读取麦克风位置的坐标
    import_mpos();

    // 关闭文件
    file.close();
}

MicGeom::~MicGeom()
{
    delete[] center_;
    delete[] mpos_;
}

const std::string &MicGeom::get_basename() const
{
    return basename_;
}

const std::vector<int> &MicGeom::get_invalid_channels() const
{
    return invalid_channels_;
}

void MicGeom::set_invalid_channels(const std::vector<int> &invalid_channels)
{
    invalid_channels_ = invalid_channels;
}

int MicGeom::get_num_mics() const
{
    return num_mics_;
}

const double *MicGeom::get_center() const
{
    return center_;
}

double MicGeom::get_aperture() const
{
    return aperture_;
}

const double *MicGeom::get_mpos() const
{
    return mpos_;
}

void MicGeom::import_mpos()
{
    // 读取麦克风位置的坐标
    mpos_ = new double[num_mics_ * 3];
    std::ifstream file(from_file_);
    // 跳过前两行
    std::string line;
    std::getline(file, line);
    std::getline(file, line);
    for (int i = 0; i < num_mics_; ++i)
    {
        std::getline(file, line);
        std::istringstream iss(line);
        iss >> mpos_[i * 3] >> mpos_[i * 3 + 1] >> mpos_[i * 3 + 2];
    }
    file.close();
}

} // namespace acoular_cpp
