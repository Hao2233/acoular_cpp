#include "trajectory.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <tuple>

#include "Eigen/Core"

namespace acoular_cpp
{
Trajectory::Trajectory() {}

Trajectory::~Trajectory() {}

void Trajectory::set_points(std::map<double, std::vector<double>> points)
{
    points_ = points;
    std::vector<double> t;
    for (auto const &[key, val] : points_)
    {
        t.push_back(key);
    }
    std::sort(t.begin(), t.end());                   // 对时间戳进行排序
    interval_ = std::make_pair(t.front(), t.back()); // 记录时间间隔
    std::vector<double> xp;
    for (auto const &[key, val] : points_)
    {
        xp.insert(xp.end(), val.begin(), val.end());
    }
    int k = std::min(3, static_cast<int>(points_.size()) - 1); // 计算样条插值的阶数
    int s = 0;
    tck_.resize(10 * points_.size()); // 分配存储空间
    int info = 0;
    splprep_(&t[0], &xp[0], &k, &s, &tck_[0], &info); // 进行样条插值
    if (info != 0)
    {
        throw std::runtime_error("Error in spline interpolation"); // 如果插值失败，则抛出异常
    }
}

std::pair<double, double> Trajectory::get_interval() const
{
    return interval_; // 返回时间间隔
}

std::vector<double> Trajectory::location(double t, int der) const
{
    std::vector<double> res(3); // 存储位置或导数
    int n = 1;
    splint_(&tck_[0], &t, &res[0], &n, &der); // 计算位置或导数
    return res;
}

std::vector<std::vector<double>> Trajectory::traj(double t_start, double t_end, double delta_t, int der) const
{
    if (delta_t <= 0)
    {
        throw std::invalid_argument("delta_t must be positive"); // 如果delta_t小于等于0，则抛出异常
    }
    if (t_start > t_end)
    {
        throw std::invalid_argument("t_start must be less than or equal to t_end"); // 如果t_start大于t_end，则抛出异常
    }
    std::vector<std::vector<double>> res; // 存储轨迹
    for (double t = t_start; t <= t_end; t += delta_t)
    {
        res.push_back(location(t, der)); // 计算位置或导数，并将其添加到轨迹中
    }
    return res;
}

// TODO ： 未完成
void Trajectory::splprep_(double *t, double *x, int *k, int *s, double *tck, int *info) const
{
    int n = (*k) + 1; // 样本点的数量
    int p = 3;        // 样条插值的阶数
    int m = n + p;    // 控制点的数量
    int sp = *s;      // 样条插值的平滑度

    // 将输入数据转换为Eigen矩阵
    Eigen::Map<Eigen::ArrayXf> T(t, n);
    Eigen::Map<Eigen::ArrayXXf> X(x, n, 3);

    // 计算样本点之间的距离
    Eigen::ArrayXf h = (T.tail(n - 1) - T.head(n - 1)).matrix();

    // 构造三对角矩阵
    Eigen::SparseMatrix<double> A(m, m);
    std::vector<Eigen::Triplet<double>> triplets;
    triplets.reserve(3 * m - 2);
    triplets.push_back(Eigen::Triplet<double>(0, 0, 1.0));
    for (int i = 1; i < n - 1; i++)
    {
        triplets.push_back(Eigen::Triplet<double>(i, i - 1, h[i - 1]));
        triplets.push_back(Eigen::Triplet<double>(i, i, 2.0 * (h[i - 1] + h[i])));
        triplets.push_back(Eigen::Triplet<double>(i, i + 1, h[i]));
    }
    triplets.push_back(Eigen::Triplet<double>(n - 1, n - 1, 1.0));
    A.setFromTriplets(triplets.begin(), triplets.end());

    // 构造右侧向量
    Eigen::ArrayXXf B(m, 3);
    B.row(0) = X.row(0);
    B.row(n - 1) = X.row(n - 1);
    for (int i = 1; i < n - 1; i++)
    {
        B.row(i) = 3.0 * ((X.row(i) - X.row(i - 1)) / h[i - 1] - (X.row(i - 1) - X.row(i - 2)) / h[i - 2]);
    }

    // 解线性方程组
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(A);
    if (solver.info() != Eigen::Success)
    {
        *info = 1; // 矩阵分解失败
        return;
    }

    Eigen::ArrayXXf C = solver.solve(B); // 计算控制点

    // 计算TCK系数
    int idx = 0;
    for (int i = 0; i < n - 1; i++)
    {
        double t1 = T[i];
        double t2 = T[i + 1];
        double h = t2 - t1;
        Eigen::ArrayXf c1 = C.row(i);
        Eigen::ArrayXf c2 = C.row(i + 1);
        Eigen::ArrayXf d1 = (c2 - c1) / (3.0 * h);
        Eigen::ArrayXf d2 = c1;
        Eigen::ArrayXf d3 = (X.row(i + 1) - X.row(i)) / h - (2.0 * c1 + c2) * h / 3.0;
        Eigen::ArrayXf d4 = X.row(i);
        for (int j = 0; j < p; j++)
        {
            tck[idx++] = d1[j];
            tck[idx++] = d2[j];
            tck[idx++] = d3[j];
            tck[idx++] = d4[j];
        }
    }

    // 将插值结果转换为输出数据
    *info = 0;
}

void Trajectory::splint_(double *tck, double *t, double *res, int *n, int *der) const
{
    int m = (*n) / 3; // 样本点的数量
    int k = 3;        // 样条插值的阶数
    int p = 3;        // 样条插值的平滑度

    // 将输入数据转换为Eigen矩阵
    Eigen::Map<Eigen::ArrayXf> T(t, m);
    Eigen::Map<Eigen::ArrayXXf> TCK(tck, 10 * m, 1);
    Eigen::ArrayXf U = (T - T[0]) / (T[T.size() - 1] - T[0]);

    // 计算插值结果
    int d = *der;
    Eigen::ArrayXXf R(m, d == 0 ? 3 : 1);
    for (int i = 0; i < m; i++)
    {
        double u = U[i];
        int j = std::min(int(u * (m - 1)), m - 2);
        double h = T[j + 1] - T[j];
        double a = (T[j + 1] - u) / h;
        double b = (u - T[j]) / h;
        double c = (1.0 / 6.0) * (a * a * a - a) * h * h;
        double d = (1.0 / 6.0) * (b * b * b - b) * h * h;
        Eigen::ArrayXf C = TCK.segment<10>(10 * j);
        if (d == 0)
        {
            R.row(i) = C.segment<3>(0) + a * C.segment<3>(3) + c * C.segment<3>(6) + d * C.segment<3>(9);
        }
        else if (d == 1)
        {
            R(i, 0) = C(3) + (2.0 * a - 1.0) * C(4) + (3.0 * a * a - 2.0 * a) * C(6) + (3.0 * b * b - 2.0 * b) * C(9);
        }
        else if (d == 2)
        {
            R(i, 0) = 2.0 * C(4) + 6.0 * a * (C(6) - C(4)) + 6.0 * b * (C(9) - C(6));
        }
    }

    // 将插值结果转换为输出数据
    Eigen::Map<Eigen::ArrayXXf> Res(res, m, d == 0 ? 3 : 1);
    Res = R;
}

} // namespace acoular_cpp