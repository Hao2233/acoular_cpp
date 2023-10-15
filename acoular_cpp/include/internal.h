#ifndef _INTERNAL_H_
#define _INTERNAL_H_

#include <string>
#include <vector>

namespace acoular_cpp
{
// 计算对象的哈希值
std::string digest(const void* obj, const std::string& name = "digest");

// 计算哈希值列表的哈希值
std::string ldigest(const std::vector<std::string>& l);

} // namespace acoular_cpp

#endif // _INTERNAL_H_