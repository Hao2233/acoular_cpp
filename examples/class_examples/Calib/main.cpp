#include "Calib.h"

#include <iostream>

int main() {
    // 创建 Calib 对象并从文件中读取数据
    acoular_cpp::Calib calib("example_calib.xml");

    // 打印文件名和麦克风数量
    std::cout << "文件名称: " << calib.get_basename() << std::endl;
    std::cout << "麦克风数据: " << calib.get_num_mics() << std::endl;

    // 打印校准数据
    std::vector<double> data = calib.get_data();

    std::cout << "校准数据:" << std::endl;
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << std::endl;
    }

    return 0;
}