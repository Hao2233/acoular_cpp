#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include <map>
#include <vector>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Sparse>

namespace acoular_cpp
{
// Trajectory class
// 作用：轨迹类，用于描述声源的运动轨迹
class Trajectory {
public:
    Trajectory();
    virtual ~Trajectory();

    // 设置轨迹点
    void set_points(std::map<float, std::vector<float>> points);

    // 获取轨迹时间间隔
    std::pair<float, float> get_interval() const;

    // 获取指定时间点的位置或其导数
    std::vector<float> location(float t, int der = 0) const;

    // 获取指定时间范围内的轨迹
    std::vector<std::vector<float>> traj(float t_start, float t_end, float delta_t, int der = 0) const;

private:
    std::map<float, std::vector<float>> points_; // 轨迹点
    std::pair<float, float> interval_; // 时间间隔
    std::vector<float> tck_; // TCK系数
    
    // 三次样条插值
    // t: 时间戳
    // x: 位置
    // k: 样条插值的阶数
    // s: 平滑因子
    // tck: TCK系数
    // info: 插值是否成功的标志
    void splprep_(float *t, float *x, int *k, int *s, float *tck, int *info) const;

    // 三次样条插值
    // tck: TCK系数
    // t: 时间戳
    // res: 位置或导数
    // n: 位置或导数的维度
    // der: 0表示位置，1表示一阶导数，2表示二阶导数
    void splint_(float *tck, float *t, float *res, int *n, int *der) const;

};
} // namespace acoular_cpp
#endif // _TRAJECTORY_H_