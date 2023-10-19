#include "internal.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cstring>

constexpr int MD5_DIGEST_LENGTH = 16;

namespace acoular_cpp
{

void md5(const unsigned char *initial_msg, size_t initial_len, unsigned char *digest)
{
    // 这些变量将包含哈希值
    unsigned int h0, h1, h2, h3;

    // 消息（要准备的）
    unsigned char *msg = nullptr;

    // 注意：所有变量都是无符号32位的，并在计算时对2^32取模

    // r指定每轮的移位量
    unsigned int r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // 使用整数的正弦的二进制整数部分（以弧度表示）作为常量
    // 初始化变量：
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;

    // 预处理：添加单个1位
    // 在消息末尾添加“1”位
    // 注意：输入字节被视为位字符串，其中第一个位是字节的最高有效位
    size_t new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;
    msg = new unsigned char[new_len + 64];
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128;

    // 预处理：添加位长度
    // 在消息末尾添加长度 mod (2 pow 64)
    uint64_t bits_len = 8 * initial_len;
    memcpy(msg + new_len, &bits_len, 8);

    // 将消息分成连续的512位块进行处理：
    // 对于每个512位的消息块：
    for (int i = 0; i < new_len; i += (512 / 8))
    {
        // 将块分成16个32位的字w[j]，其中0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *)(msg + i);

        // 为此块初始化哈希值：
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        // 主循环：
        for (int j = 0; j < 64; j++)
        {
            uint32_t f, g;

            if (j < 16)
            {
                f = (b & c) | ((~b) & d);
                g = j;
            }
            else if (j < 32)
            {
                f = (d & b) | ((~d) & c);
                g = (5 * j + 1) % 16;
            }
            else if (j < 48)
            {
                f = b ^ c ^ d;
                g = (3 * j + 5) % 16;
            }
            else
            {
                f = c ^ (b | (~d));
                g = (7 * j) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            // 左移
            b = b + ((a + f + k[j] + w[g]) << r[j]);
            a = temp;
        }

        // 将此块的哈希添加到到目前为止的结果中：
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }

    // 清理
    delete[] msg;

    // var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    memcpy(digest, &h0, sizeof(h0));
    memcpy(digest + sizeof(h0), &h1, sizeof(h1));
    memcpy(digest + sizeof(h0) + sizeof(h1), &h2, sizeof(h2));
    memcpy(digest + sizeof(h0) + sizeof(h1) + sizeof(h2), &h3, sizeof(h3));
}

std::string digest(const void *obj, const std::string &name = "digest")
{
    std::vector<std::string> str_;
    str_.push_back(typeid(obj).name());
    // 通过“.”分割名称
    std::stringstream ss(name);
    std::string item;
    while (std::getline(ss, item, '.'))
    {
        // 获取属性的值
        std::string value;
        std::stringstream ss2(item);
        std::getline(ss2, value, '[');
        auto vobj = obj;
        while (std::getline(ss2, value, '['))
        {
            if (value.back() == ']')
            {
                value.pop_back();
            }
            auto index = std::stoi(value);
            vobj = static_cast<const std::vector<void *> *>(vobj)->at(index);
        }
        // 将值转换为字符串
        std::stringstream ss3;
        ss3 << vobj;
        str_.push_back(ss3.str());
    }
    // 计算md5哈希
    std::stringstream ss4;
    for (const auto &s : str_)
    {
        ss4 << s;
    }
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    md5(reinterpret_cast<const unsigned char *>(ss4.str().c_str()), ss4.str().size(), md5_hash);
    std::stringstream ss5;
    ss5 << '_';
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        ss5 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(md5_hash[i]);
    }
    return ss5.str();
}

std::string ldigest(const std::vector<void *> &l)
{
    std::vector<std::string> str_;
    for (const auto &i : l)
    {
        str_.push_back(digest(i, "digest"));
    }
    // 计算md5哈希
    std::stringstream ss4;
    for (const auto &s : str_)
    {
        ss4 << s;
    }
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    md5(reinterpret_cast<const unsigned char *>(ss4.str().c_str()), ss4.str().size(), md5_hash);
    std::stringstream ss5;
    ss5 << '_';
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        ss5 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(md5_hash[i]);
    }
    return ss5.str();
}
} // namespace acoular_cpp