#include "Calib.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>

#include "internal.h"

namespace acoular_cpp
{
Calib::Calib(const std::string& from_files) : from_file(from_files), num_mics(0)
{
    import_data();
}

std::string Calib::get_basename() const {
    return from_file;
}

int Calib::get_num_mics() const {
    return num_mics;
}

std::vector<double> Calib::get_data() const {
    return data;
}

void Calib::import_data() {
    if (!std::ifstream(from_file)) {
        // 空文件
        data.resize(1);
        data[0] = 1.0;
        num_mics = 1;
        return;
    }

    std::vector<std::string> names;
    std::ifstream file(from_file);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("<pos") != std::string::npos) {
            std::string name = line.substr(line.find("Name=\"") + 6);
            name = name.substr(0, name.find("\""));
            names.push_back(name);

            std::string factor = line.substr(line.find("factor=\"") + 8);
            factor = factor.substr(0, factor.find("\""));
            data.push_back(std::stod(factor));
        }
    }
    // 麦克风数量
    num_mics = names.size();

    file.close();
}
} // namespace acoular_cpp