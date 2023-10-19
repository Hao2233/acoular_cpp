#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include <map>
#include <vector>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Sparse>

namespace acoular_cpp
{
/**
 * @brief 轨迹类，用于描述声源的运动轨迹
 */
class Trajectory
{
public:
    /**
     * @brief 构造函数
     */
    Trajectory();

    /**
     * @brief 析构函数
     */
    virtual ~Trajectory();

    /**
     * @brief 设置轨迹点
     * @param points 轨迹点
     */
    void set_points(std::map<double, std::vector<double>> points);

    /**
     * @brief 获取轨迹时间间隔
     * @return 时间间隔
     */
    std::pair<double, double> get_interval() const;

    /**
     * @brief 获取指定时间点的位置或其导数
     * @return 时间点的位置或导数
     */
    std::vector<double> location(double t, int der = 0) const;

    /**
     * @brief 获取指定时间范围内的轨迹
     * @return 轨迹
     */
    std::vector<std::vector<double>> traj(double t_start, double t_end, double delta_t, int der = 0) const;

private:
    std::map<double, std::vector<double>> points_; // 轨迹点
    std::pair<double, double> interval_;           // 时间间隔
    std::vector<double> tck_;                      // TCK系数

    /**
     * @brief 三次样条插值
     * @param t 时间戳
     * @param x 位置
     * @param k 样条插值的阶数
     * @param s 平滑因子
     * @param tck TCK系数
     * @param info 插值是否成功的标志
     */
    void splprep_(double *t, double *x, int *k, int *s, double *tck, int *info) const;

    /**
     * @brief 三次样条插值
     * @param tck TCK系数
     * @param t 时间戳
     * @param res 位置或导数
     * @param n 位置或导数的维度
     * @param der 0表示位置，1表示一阶导数，2表示二阶导数
     */
    void splint_(double *tck, double *t, double *res, int *n, int *der) const;
};
} // namespace acoular_cpp
#endif // _TRAJECTORY_H_