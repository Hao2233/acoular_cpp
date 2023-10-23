#ifndef _LOG_STATUS_H_
#define _LOG_STATUS_H_

namespace acoular_cpp
{
/**
 * @brief log日志类型
 * 
 */
enum log_status
{
    /**
     * @brief 正常 没有错误
     * 
     */
    INFO = 0x0000,

    /**
     * @brief 警告
     * 
     */
    WARNING = 0x0010,

    /**
     * @brief 错误 致命错误
     * 
     */
    ERROR = 0x1111,

    /**
     * @brief 文件错误
     * 
     */
    ERROR_FILE = 0x0011,

};
}   // namespace acoular_cpp
#endif // _LOG_STATUS_H_