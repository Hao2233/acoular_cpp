#ifndef _LINEARNDINTERPOLATOR_H_
#define _LINEARNDINTERPOLATOR_H_

#include <vector>
#include <cmath>

namespace acoular_cpp
{
/**
 * @brief 用于多维线性插值的类
 *
 */
class LinearNDInterpolator
{
public:
    std::vector<std::vector<double>> points; /**< 插值点的坐标 */
    std::vector<double> values;              /**< 插值点的值 */

    /**
     * @brief 构造函数
     *
     * @param _points 插值点的坐标
     * @param _values 插值点的值
     */
    LinearNDInterpolator(std::vector<std::vector<double>> _points, std::vector<double> _values);

    /**
     * @brief 构造函数
     */
    LinearNDInterpolator() = default;

    /**
     * 插值函数
     * @param point 插值点
     * @return 插值结果
     */
    double operator()(std::vector<double> point) ;

private:
    /**
     * @brief 找到距离插值点最近的点的索引
     *
     * @param x 插值点的坐标
     * @return std::vector<int> 最近的点的索引
     */
    std::vector<int> _find_indices(std::vector<double> x);

    /**
     * @brief 计算插值点到最近的点的距离
     *
     * @param x 插值点的坐标
     * @param indices 最近的点的索引
     * @return std::vector<double> 插值点到最近的点的距离
     */
    std::vector<double> _find_dists(std::vector<double> x, std::vector<int> indices);

    /**
     * @brief 计算每个最近的点的权重
     *
     * @param dists 插值点到最近的点的距离
     * @return std::vector<double> 每个最近的点的权重
     */
    std::vector<double> _find_weights(std::vector<double> dists);

    /**
     * @brief 进行插值
     *
     * @param indices 最近的点的索引
     * @param weights 每个最近的点的权重
     * @return  插值结果
     */
    double _interpolate(std::vector<int> indices, std::vector<double> weights);
};
} // namespace acoul
#endif // _LINEARNDINTERPOLATOR_H_