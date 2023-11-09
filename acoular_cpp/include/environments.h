#ifndef _ENVIRONMENTS_H_
#define _ENVIRONMENTS_H_

#include <cmath>
#include <vector>
#include <string>
#include <tuple>
#include <numeric>

#include "LinearNDInterpolator.h"
#include "ConvexHull.h"

namespace acoular_cpp
{
/**
 * @brief 计算两个点之间的距离
 * @param gpos 一个包含三个浮点数的数组， 
 * @param mpos 一个包含三个浮点数的数组， 
 * @return 一个包含两个浮点数的数组， 表示距离矩阵
*/
std::vector<std::vector<double>> dist_mat(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos);

/**
 * @brief 将笛卡尔坐标转换为柱坐标
 * @param x 一个包含三个浮点数的数组， 
 * @param Q 一个包含三个数组的数组， 表示一个旋转矩阵
 * @return 一个包含三个浮点数的数组， 表示柱坐标
*/
std::vector<std::vector<double>> cartToCyl(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q);

/**
 * @brief 将柱坐标转换为笛卡尔坐标
 * @param x 一个包含三个浮点数的数组， 表示一个点的坐标
 * @param Q 一个包含三个数组的数组， 表示一个旋转矩阵
 * @return 一个包含三个浮点数的数组， 表示笛卡尔坐标
*/
std::vector<std::vector<double>> cylToCart(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q);

/**
 * @brief 用于光线投射的内部辅助函数，其中包含在一个球体的一部分上给出等分布方向的单位向量
 * @param N 要生成的方向数
 * @param Om 要覆盖的球体部分的立体角
 * @param b 要覆盖的球体部分的中心方向
 * @return 函数返回一个二维向量，其中每行表示一个方向作为笛卡尔坐标中的单位向量。
*/
std::vector<std::vector<double>> spiral_sphere(int N, double Om = 2 * M_PI, std::vector<double> b = {0, 0, 1});

/**
 * @brief 用于计算输入数组X的矩阵
 * @param x 一个包含浮点数的二维数组，表示一个矩阵或向量
 * @param ord 范数的阶数
 * @param axis： 范数计算的轴
 * @param keepdims： 如果为true，则保留轴上的尺寸
 * @return 一个包含浮点数的一维数组，表示范数
*/
std::vector<double> norm(std::vector<std::vector<double>> x, double ord = 2, int axis = -1, bool keepdims = false);

/**
 * @brief 
 * @param x 一个包含浮点数的二维数组，表示一个矩阵或向量
 * @param ord 范数的阶数
 * @return 一个包含浮点数的一维数组，表示范数
*/
double norm(std::vector<std::vector<double>> x, double ord = 2);

/**
 * @brief 用于计算输入数组X的范数
 * @param x 一个包含浮点数的一维数组，表示一个向量
 * @param ord 范数的阶数
 * @return 一个包含浮点数的一维数组，表示范数
*/
double norm(std::vector<double> x, double ord = 2);

/**
 * @brief 环境类，用于计算声学环境中的声学参数
 */
class Environment
{
private:
    std::string digest; ///< 用于缓存计算结果的哈希值

    /**
     * @brief 计算哈希值
     * @return 哈希值
     */
    std::string get_digest();

public:
    double c = 343.0; ///< 声速，单位为 m/s

    std::vector<std::vector<double>> roi; ///< 区域 of interest，用于指定声学计算的区域
    /**
     * @brief 计算声源和接收点之间的距离
     * @param gpos 声源位置，每行为一个声源的坐标，列数为 3
     * @param mpos 接收点位置，每行为一个接收点的坐标，列数为 3，默认为 (0, 0, 0)
     * @return 声源和接收点之间的距离矩阵，每行为一个声源到所有接收点的距离，列数为接收点数
     */
    std::vector<std::vector<double>> r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos = {{0.0, 0.0, 0.0}});
};

/**
 * @brief 均匀流场环境类，用于描述均匀流场环境
 */
class UniformFlowEnvironment
{
private:
    double ma = 0.0;                           /**< 马赫数 */
    std::vector<double> fdv = {1.0, 0.0, 0.0}; /**< 流动方向向量 */
    std::string digest;                        /**< 哈希值 */

    /**
     * @brief 计算声源到各个测点的距离
     * @param gpos 测点位置
     * @param mpos 声源位置
     * @return 各个测点到声源的距离
     */
    std::vector<std::vector<double>> _r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos = {{0.0, 0.0, 0.0}});

public:
    UniformFlowEnvironment() = default;
    ~UniformFlowEnvironment() = default;

    /**
     * @brief 计算声源到各个测点的距离
     * @param gpos 测点位置
     * @param mpos 声源位置
     * @return 各个测点到声源的距离
     */
    std::vector<std::vector<double>> r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos = {{0.0, 0.0, 0.0}});
};

/**
 * @brief 流场类，提供流场速度场的计算
 */
class FlowField
{
public:
    /**
     * @brief 返回一个元组，包含速度和速度梯度
     * 
     * @param xx 输入的位置坐标
     * @return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 
     *         元组，第一个元素是速度，第二个元素是速度梯度
     */
    virtual std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx)
    {
        std::vector<double> v(3, 0.0);
        std::vector<std::vector<double>> dv(3, std::vector<double>(3, 0.0));
        return std::make_tuple(v, dv);
    }
};

/**
 * @brief SlotJet类，继承自FlowField类，表示一个具有槽口的气流场。
 */
class SlotJet : public FlowField
{
public:
    SlotJet() = default;
    virtual ~SlotJet() = default;

    double v0 = 0.0;                              /**< 初始速度 */
    std::vector<double> origin = {0.0, 0.0, 0.0}; /**< 坐标原点 */
    std::vector<double> flow = {1.0, 0.0, 0.0};   /**< 气流方向 */
    std::vector<double> plane = {0.0, 1.0, 0.0};  /**< 平面法向量 */
    double B = 0.2;                               /**< 槽口宽度 */

    /**
     * @brief 计算在给定位置的速度和雅可比矩阵。
     *
     * @param xx 给定位置的坐标
     * @return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 返回速度和雅可比矩阵
     */
    std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override;

    std::string digest = ""; /**< 哈希值 */
};

/**
 * @brief OpenJet类，继承自FlowField类，表示开放式喷流环境
 *
 */
class OpenJet : public FlowField
{
public:
    OpenJet() = default;
    virtual ~OpenJet() = default;

    double v0 = 0.0;                              /**< 喷流速度 */
    std::vector<double> origin = {0.0, 0.0, 0.0}; /**< 喷流起点坐标 */
    double D = 0.1;                               /**< 喷流直径 */

    /**
     * @brief 计算某一点的速度和雅可比矩阵
     *
     * @param xx 空间坐标
     * @return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 速度和雅可比矩阵
     */
    std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override;

    std::string digest = ""; /**< 哈希值 */
};

/**
 * @brief 旋转流场类，继承自FlowField类
 */
class RotatingFlow : public FlowField
{
public:
    RotatingFlow() = default;
    virtual ~RotatingFlow() = default;

    /**
     * @brief 转速，单位为rpm
     */
    double rpm = 0.0;

    /**
     * @brief 初始速度
     */
    double v0 = 0.0;

    /**
     * @brief 旋转中心坐标
     */
    std::vector<double> origin = {0.0, 0.0, 0.0};

    /**
     * @brief 计算速度和雅可比矩阵
     * @param xx 空间坐标
     * @return 返回速度和雅可比矩阵
     */
    std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override;

    /**
     * @brief 用于校验流场是否相同
     */
    std::string digest = "";
};

/**
 * @brief 旋转流场环境类，继承自Environment类
 */
class GeneralFlowEnvironment : public Environment, FlowField
{
public:
    FlowField ff; // 流场
    int N;        // 网格数
    double Om;    // 角频率

    /**
     * @brief 构造函数
     * @param _ff 流场
     * @param _N 网格数
     * @param _Om 角频率
     */
    GeneralFlowEnvironment(Environment _ff, int _N = 200, double _Om = M_PI);

    /**
     * @brief 计算声源到麦克风的距离
     * @param gpos 声源位置
     * @param mpos 麦克风位置
     * @return 声源到麦克风的距离
     */
    std::vector<std::vector<double>> _r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos = {{0, 0, 0}});

    /**
     * @brief 获取插值器
     * @param roi 区域
     * @param x0 坐标
     * @return 插值器
     */
    LinearNDInterpolator get_interpolator(std::vector<std::vector<double>> roi, std::vector<double> x0);
private:
    double c = 343.0; // 空气中的声速

    /**
     * @brief 用于缓存计算结果的哈希值
     */
    std::unordered_map<std::tuple<double, double, double>, LinearNDInterpolator> idict;

    /**
     * @brief 具体来说，hstack 函数将多个数组按列方向拼接成一个新的数组，要求这些数组在除了列数之外的维度上的形状必须相同。
     * @param a 数组 a
     * @param b 数组 b
    */
    std::vector<double> hstack(std::vector<double> a, std::vector<double> b);
};
} // namespace acoular_cpp
#endif // _ENVIRONMENTS_H_