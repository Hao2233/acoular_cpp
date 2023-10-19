#ifndef _CONVEXHULL_H_
#define _CONVEXHULL_H_

#include <vector>
#include <algorithm>

namespace acoular_cpp
{
/**
 * @brief ConvexHull类用于计算二维点集的凸包
 */
class ConvexHull
{
public:
    std::vector<std::vector<double>> points; /**< 存储点集的二维坐标 */
    std::vector<int> vertices;               /**< 存储凸包的顶点编号 */
    std::vector<std::vector<int>> simplices; /**< 存储凸包的三角形面片 */

    /**
     * @brief 构造函数，计算给定点集的凸包
     * @param _points 给定的点集，每个元素为一个二维坐标
     */
    ConvexHull(std::vector<std::vector<double>> _points);

    /**
     * @brief ConvexHull类的构造函数，用于计算给定点集的凸包
     *
     * @param _points 给定的点集，每个元素是一个二维坐标点的vector
     * @param _values 给定的点集对应的值，每个元素是一个值的vector
     */
    ConvexHull(std::vector<std::vector<double>> _points, std::vector<std::vector<double>> _values);

private:
    /**
     * @brief 计算凸包的内部函数
     */
    void _compute_hull();

    /**
     * @brief 计算三个点组成的向量的叉积
     * @param i 第一个点的编号
     * @param j 第二个点的编号
     * @param k 第三个点的编号
     * @return 三个点组成的向量的叉积
     */
    double _cross(int i, int j, int k);

    /**
     * @brief 计算凸包的三角形面片
     * @return 存储凸包的三角形面片的二维数组
     */
    std::vector<std::vector<int>> _compute_simplices();
};
} // namespace acoular_cpp
#endif // _CONVEXHULL_H_