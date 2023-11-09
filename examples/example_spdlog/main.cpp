#include <iostream>

// spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main()
{   
    // example spdlog 输出信息
    spdlog::info("Welcome to spdlog!");

    // example spdlog 输出信息到文件
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
    file_logger->info("Welcome to spdlog!");

    // example spdlog 文件名称为当前日期
    auto daily_logger = spdlog::daily_logger_mt("daily_logger", "logs/daily-log.txt");
    daily_logger->info("Welcome to spdlog!");

    // example spdlog 输出日志到文件，文件名称为当前日期，后缀名为.log
    auto rotating_logger = spdlog::rotating_logger_mt("file_logger", "logs/rotating-log.log", 1024 * 1024 * 5, 3);
    rotating_logger->info("Welcome to spdlog!");

    return 0;
}