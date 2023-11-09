#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <unordered_map>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/Geometry>

#include "configuration.h"

namespace acoular_cpp
{

// TODO: 未完成 
    class H5cache_class
    {
    public:
        H5cache_class(const Config &config) : config_(config) {}

        // Cache directory
        std::string cache_dir() const
        {
            return config_.cache_dir();
        }

        // Check if cache is busy
        bool busy() const
        {
            return busy_;
        }

        // Open a file
        std::shared_ptr<TableFile> open_file(const std::string &filename)
        {
            // Check if file is already open
            auto it = open_files_.find(filename);
            if (it != open_files_.end())
            {
                // Increment reference count
                open_file_reference_count_[filename]++;
                return it->second;
            }
            // Open file
            std::shared_ptr<TableFile> file = std::make_shared<TableFile>(filename);
            open_files_[filename] = file;
            open_file_reference_count_[filename] = 1;
            return file;
        }

        // Close a file
        void close_file(const std::string &filename)
        {
            // Decrement reference count
            open_file_reference_count_[filename]--;
            if (open_file_reference_count_[filename] == 0)
            {
                // Close file
                open_files_.erase(filename);
                open_file_reference_count_.erase(filename);
            }
        }

    private:
        Config config_;
        bool busy_ = false;
        std::unordered_map<std::string, std::shared_ptr<TableFile>> open_files_;
        std::unordered_map<std::string, int> open_file_reference_count_;
    };
} // namespace acoular_cpp