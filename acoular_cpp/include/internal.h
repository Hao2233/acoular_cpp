#ifndef _INTERNAL_H_
#define _INTERNAL_H_

#include <string>
#include <vector>

namespace acoular_cpp
{

/**
 * @brief 计算对象的哈希值
 * @param obj 对象
 * @param name 名字
*/
std::string digest(const void* obj, const std::string& name = "digest");

/**
 * @brief 计算哈希列表的哈希值
 * @param 哈希列表
 * @return 哈希值
*/
std::string ldigest(const std::vector<std::string>& l);

} // namespace acoular_cpp
#endif // _INTERNAL_H_