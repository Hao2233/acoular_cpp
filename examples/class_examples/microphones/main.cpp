#include "microphones.h"

#include <iostream>

int main() {
    try {
        // 创建MicGeom对象并从文件中读取麦克风阵列的几何信息
        acoular_cpp::MicGeom mic_geom("array_64.xml", true);

        // 输出阵列中心的坐标和孔径
        const double* center = mic_geom.get_center();
        std::cout << "Center: (" << center[0] << ", " << center[1] << ", " << center[2] << ")" << std::endl;
        std::cout << "Aperture: " << mic_geom.get_aperture() << std::endl;

        // 输出麦克风数量和位置的坐标
        int num_mics = mic_geom.get_num_mics();
        const double* mpos = mic_geom.get_mpos();
        std::cout << "Number of microphones: " << num_mics << std::endl;
        for (int i = 0; i < num_mics; ++i) {
            std::cout << "Microphone " << i << ": (" << mpos[i * 3] << ", " << mpos[i * 3 + 1] << ", " << mpos[i * 3 + 2] << ")" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
