#ifndef _GRIDS_H_
#define _GRIDS_H_

#include <cmath>
#include <vector>
#include <iostream>
#include <tuple>
#include <string>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/Geometry>

namespace acoular_cpp
{

/**
 * @brief 多边形类，用于描述阵元的位置
 *  
*/
class Polygon
{
public:
    /**
     * @brief 构造函数,根据阵元的位置构造多边形
     * @param x 阵元的x坐标
     * @param y 阵元的y坐标
    */
    Polygon(const std::vector<double> &x, const std::vector<double> &y);

    /**
     * @brief 判断点是否中多边形内部
     * @param xpoint 点的x坐标
     * @param ypoint 点的y坐标
     * @param smalld 误差
     * @return 如果点在多边形内部，则返回1，否则返回0
    */
    double is_inside(double xpoint, double ypoint, double smalld = 1e-12) const;

    /**
     * @brief 计算行列式
     * @param x 阵元的x坐标
     * @param y 阵元的y坐标
     * @return 行列式的值
    */
    double det(const std::vector<double> &x, const std::vector<double> &y) const;

private:
    // x_ : 阵元的x坐标
    std::vector<double> x_;
    // y_ : 阵元的y坐标
    std::vector<double> y_;
};

/**
 * @brief 网格类，用于描述阵元的位置
*/
class Grid
{
public:
    /**
     * @brief 析构函数
    */
    virtual ~Grid() {}

    /**
     * @brief 网格点总数。只读；当设置其他网格定义属性时自动设置
     * @return 网格点总数
    */
    virtual int size() const = 0;

    /**
     * @brief 网格形状。只读，以元组的形式给出，对于笛卡尔网格很有用
     * @return 元组 网格形状
    */
    virtual std::tuple<int, int> shape() const = 0;

    /**
     * @brief 网格位置，只读 作为大小为(3, size)的浮点数数组，不包括无效的麦克风
     * @return 网格位置
    */
    virtual Eigen::MatrixXd gpos() const = 0;

    /**
     * @brief 内部标识符
     * @return 内部标识符
    */
    virtual std::string digest() const = 0;

    /**
     * @brief 计算网格坐标 已弃用；请改用gpos()属性。
    */
    virtual Eigen::MatrixXd pos() const
    {
        return gpos();
    }

    /**
     * @brief 查询网格中子域的索引 允许任意类型的扇形子域。
    */
    std::tuple<Eigen::ArrayXi, Eigen::ArrayXi> subdomain(const Grid &grid, const Sector &sector) const;
};

/**
 * @brief 扇形类，用于描述阵元的位置
*/
class Sector
{
public:
    /**
     * @brief 析构函数
    */
    virtual ~Sector() {}

    /**
     * @brief 查询给定数组中的坐标是否位于定义的扇形内 对于此扇形类型，任何位置都是有效的
    */
    virtual Eigen::Array<bool, Eigen::Dynamic, 1> contains(const Eigen::MatrixXd &pos) const
    {
        return Eigen::Array<bool, Eigen::Dynamic, 1>::Ones(pos.cols());
    }

    // 布尔标志，如果为“true”（默认值），则包括位于扇形边界上的网格点。
    bool include_border = true;

    // 扇形边界的绝对公差
    double abs_tol = 1e-12;

    // 布尔标志，如果为“true”（默认值），则如果没有网格点位于扇形内，则返回最近的网格点。
    bool default_nearest = true;
};

} // namespace acoular_cpp
#endif // _GRIDS_H_