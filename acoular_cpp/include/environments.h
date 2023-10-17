#ifndef _ENVIRONMENTS_H_
#define _ENVIRONMENTS_H_

#include <cmath>
#include <vector>
#include <string>
#include <tuple>
#include <numeric>

namespace acoular_cpp
{
// 作用： 计算两个点之间的距离
// gpos： 一个包含三个浮点数的数组， 表示一个点的坐标
// mpos： 一个包含三个浮点数的数组， 表示一个点的坐标
// 返回值： 一个包含两个浮点数的数组， 表示距离矩阵
std::vector<std::vector<double>> dist_mat(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos);

// 作用： 将笛卡尔坐标转换为柱坐标
// x： 一个包含三个浮点数的数组， 表示一个点的坐标
// Q： 一个包含三个数组的数组， 表示一个旋转矩阵
// 返回值： 一个包含三个浮点数的数组， 表示柱坐标
std::vector<std::vector<double>> cartToCyl(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q);

// 作用： 将柱坐标转换为笛卡尔坐标
// x： 一个包含三个浮点数的数组， 表示一个点的坐标
// Q： 一个包含三个数组的数组， 表示一个旋转矩阵
// 返回值： 一个包含三个浮点数的数组， 表示笛卡尔坐标
std::vector<std::vector<double>> cylToCart(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q);

// 作用： 用于光线投射的内部辅助函数，其中包含在一个球体的一部分上给出等分布方向的单位向量
// N： 要生成的方向数
// Om： 要覆盖的球体部分的立体角
// b： 要覆盖的球体部分的中心方向
// 函数返回一个二维向量，其中每行表示一个方向作为笛卡尔坐标中的单位向量。
std::vector<std::vector<double>> spiral_sphere(int N, double Om=2*M_PI, std::vector<double> b={0, 0, 1});

// 作用：用于计算输入数组X的矩阵
// x： 一个包含浮点数的二维数组，表示一个矩阵或向量
// ord： 范数的阶数
// axis： 范数计算的轴
// keepdims： 如果为true，则保留轴上的尺寸
// 返回值： 一个包含浮点数的一维数组，表示范数
std::vector<double> norm(std::vector<std::vector<double>> x, double ord = 2, int axis = -1, bool keepdims = false);

// 作用：用于计算输入数组X的范数
// x： 一个包含浮点数的二维数组，表示一个矩阵或向量
// ord： 范数的阶数
// 返回值： 一个包含浮点数的一维数组，表示范数
double norm(std::vector<std::vector<double>> x, double ord = 2);

// 作用：用于计算输入数组X的范数
// x： 一个包含浮点数的一维数组，表示一个向量
// ord： 范数的阶数
// 返回值： 一个包含浮点数的一维数组，表示范数
double norm(std::vector<double> x, double ord = 2);

/**
 * @brief 环境类，用于计算声学环境中的声学参数
 */
class Environment {
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
class UniformFlowEnvironment {
private:
    double ma = 0.0; /**< 马赫数 */
    std::vector<double> fdv = {1.0, 0.0, 0.0}; /**< 流动方向向量 */
    std::string digest; /**< 哈希值 */

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
class FlowField {
public:
    /**
     * @brief 构造函数
     */
    FlowField() = default;
    /**
     * @brief 析构函数
     */
    ~FlowField() = default;

    /**
     * @brief 计算流场速度场
     * @param xx 流场位置
     * @return 返回速度场和速度梯度场
     */
    std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) ;

    /**
     * @brief 流场的唯一标识符
     */
    std::string digest = "";
};

/**
 * @brief SlotJet类，继承自FlowField类，表示一个具有槽口的气流场。
 */
class SlotJet : public FlowField {
public:
    
    SlotJet() = default;
    virtual ~SlotJet() = default;

    double v0 = 0.0; /**< 初始速度 */
    std::vector<double> origin = {0.0, 0.0, 0.0}; /**< 坐标原点 */
    std::vector<double> flow = {1.0, 0.0, 0.0}; /**< 气流方向 */
    std::vector<double> plane = {0.0, 1.0, 0.0}; /**< 平面法向量 */
    double B = 0.2; /**< 槽口宽度 */

    /**
     * @brief 计算在给定位置的速度和雅可比矩阵。
     * 
     * @param xx 给定位置的坐标
     * @return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 返回速度和雅可比矩阵
     */
    std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override ;

    std::string digest = ""; /**< 哈希值 */
};

/**
 * @brief OpenJet类，继承自FlowField类，表示开放式喷流环境
 * 
*/
class OpenJet : public FlowField {
public:
    OpenJet() = default;
    virtual ~OpenJet() = default;

    double v0 = 0.0; /**< 喷流速度 */
    std::vector<double> origin = {0.0, 0.0, 0.0}; /**< 喷流起点坐标 */
    double D = 0.1; /**< 喷流直径 */

    /**
     * @brief 计算某一点的速度和雅可比矩阵
     * 
     * @param xx 空间坐标
     * @return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 速度和雅可比矩阵
     */
    std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override ;

    std::string digest = ""; /**< 哈希值 */
};

/**
* @brief 旋转流场类，继承自FlowField类
*/
class RotatingFlow : public FlowField {
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
    std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override ;

    /**
     * @brief 用于校验流场是否相同
     */
    std::string digest = "";
};

// TODO ： 有BUG 明天修改
// 具有通用流场的声学环境类
class GeneralFlowEnvironment : public Environment {
public:
    GeneralFlowEnvironment(const FlowField& ff) : ff(ff) {}

    // The flow field, must be of type FlowField.
    FlowField ff;

    // Number of rays used per solid angle Ω, defaults to 200.
    int N = 200;

    // The maximum solid angle used in the algorithm, defaults to π.
    double Om = M_PI;

    // Calculates the virtual distances between grid point locations and
    // microphone locations or the origin. These virtual distances correspond
    // to travel times of the sound along a ray that is traced through the
    // medium.
    std::vector<std::vector<double>> r(const std::vector<std::array<double, 3>>& gpos,
                                        const std::vector<std::array<double, 3>>& mpos = {{0, 0, 0}}) {
        double c = this->c;

        std::vector<std::vector<double>> gt(gpos.size(), std::vector<double>(mpos.size()));
        for (size_t micnum = 0; micnum < mpos.size(); micnum++) {
            const auto& x0 = mpos[micnum];
            auto key = std::to_string(x0[0]) + "," + std::to_string(x0[1]) + "," + std::to_string(x0[2]);
            try {
                auto& li = this->idict.at(key); // fetch stored interpolator
                // do the interpolation
                for (size_t i = 0; i < gpos.size(); i++) {
                    gt[i][micnum] = li(gpos[i].data());
                }
            } catch (const std::out_of_range&) {
                // if interpolator doesn't exist, construct it
                auto roi = gpos;
                if (!this->roi.empty()) {
                    roi = this->roi;
                }
                auto li = this->get_interpolator(roi, x0);
                this->idict.emplace(key, li);
                // do the interpolation
                for (size_t i = 0; i < gpos.size(); i++) {
                    gt[i][micnum] = li(gpos[i].data());
                }
            }
        }
        if (gt.size() == 1) {
            gt = {gt[0]};
        }
        for (auto& row : gt) {
            std::transform(row.begin(), row.end(), row.begin(), [c](double d) { return c * d; });
        }
        return gt;
    }

private:
    // internal identifier
    std::string digest() const {
        // implementation details omitted
        return "";
    }

    // internal dictionary of interpolators
    std::unordered_map<std::string, std::function<double(const double*)>> idict;

    // gets a function that interpolates travel times along a ray
    std::function<double(const double*)> get_interpolator(const std::vector<std::array<double, 3>>& roi,
                                                           const std::array<double, 3>& x0) const {
        double c = this->c;

        // the DE system
        auto f1 = [c, &v = this->ff.v](double t, const double* y) -> std::array<double, 6> {
            std::array<double, 3> x{y[0], y[1], y[2]};
            std::array<double, 3> s{y[3], y[4], y[5]};
            auto [vv, dv] = v(x);
            double sa = std::sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
            std::array<double, 6> xout;
            xout[0] = c * s[0] / sa - vv[0]; // time reversal
            xout[1] = c * s[1] / sa - vv[1]; // time reversal
            xout[2] = c * s[2] / sa - vv[2]; // time reversal
            xout[3] = -s[0] * dv[0][0] - s[1] * dv[1][0] - s[2] * dv[2][0]; // time reversal
            xout[4] = -s[0] * dv[0][1] - s[1] * dv[1][1] - s[2] * dv[2][1]; // time reversal
            xout[5] = -s[0] * dv[0][2] - s[1] * dv[1][2] - s[2] * dv[2][2]; // time reversal
            return xout;
        };

        // integration along a single ray
        auto fr = [c, &v = this->ff.v](const std::array<double, 3>& x0, const std::array<double, 3>& n0, double rmax,
                                       double dt, std::vector<std::array<double, 3>>& xyz, std::vector<double>& t) {
            std::array<double, 6> y0{0, 0, 0, n0[0] / (c + v(x0)[0] * n0[0]), n0[1] / (c + v(x0)[1] * n0[1]),
                                     n0[2] / (c + v(x0)[2] * n0[2])};
            auto f1_wrapper = [&f1, &v](double t, const double* y) -> std::array<double, 6> {
                return f1(t, y, v);
            };
            auto oo = ode(f1_wrapper);
            oo.set_integrator("vode", 1e-4, 1e-4 * rmax);
            oo.set_initial_value(y0.data(), 0);
            while (oo.successful()) {
                std::array<double, 3> x{oo.y[0], oo.y[1], oo.y[2]};
                xyz.push_back(x);
                t.push_back(oo.t);
                if (std::sqrt((x[0] - x0[0]) * (x[0] - x0[0]) + (x[1] - x0[1]) * (x[1] - x0[1]) +
                              (x[2] - x0[2]) * (x[2] - x0[2])) > rmax) {
                    break;
                }
                oo.integrate(oo.t + dt);
            }
        };

        size_t gs2 = roi.size();
        auto vv = this->ff.v;
        int NN = std::sqrt(this->N);
        std::array<double, 3> xe{0, 0, 0};
        for (const auto& p : roi) {
            xe[0] += p[0];
            xe[1] += p[1];
            xe[2] += p[2];
        }
        xe[0] /= roi.size();
        xe[1] /= roi.size();
        xe[2] /= roi.size();
        std::vector<std::array<double, 3>> r;
        for (const auto& p : roi) {
            r.push_back({x0[0] - p[0], x0[1] - p[1], x0[2] - p[2]});
        }
        double rmax = std::sqrt(std::max_element(r.begin(), r.end(),
                                                 [](const auto& a, const auto& b) {
                                                     return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] <
                                                            b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
                                                 })->operator[](0) *
                                std::max_element(r.begin(), r.end(),
                                                 [](const auto& a, const auto& b) {
                                                     return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] <
                                                            b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
                                                 })->operator[](0) +
                            std::max_element(r.begin(), r.end(),
                                             [](const auto& a, const auto& b) {
                                                 return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] <
                                                        b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
                                             })->operator[](1) *
                                std::max_element(r.begin(), r.end(),
                                                 [](const auto& a, const auto& b) {
                                                     return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] <
                                                            b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
                                                 })->operator[](1) +
                            std::max_element(r.begin(), r.end(),
                                             [](const auto& a, const auto& b) {
                                                 return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] <
                                                        b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
                                             })->operator[](2) *
                                std::max_element(r.begin(), r.end(),
                                                 [](const auto& a, const auto& b) {
                                                     return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] <
                                                            b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
                                                 })->operator[](2));
        std::vector<std::array<double, 3>> nv = spiral_sphere(this->N, this->Om, xe - x0);
        double rstep = rmax / std::sqrt(this->N);
        rmax += rstep;
        double tstep = rstep / c;
        std::vector<std::array<double, 3>> xyz;
        std::vector<double> t;
        size_t lastind = 0;
        for (size_t i = 0; i < nv.size(); i++) {
            fr(x0, nv[i], rmax, tstep, xyz, t);
            if (i && i % NN == 0) {
                if (!lastind) {
                    std::vector<std::array<double, 3>> points;
                    for (const auto& p : roi) {
                        points.push_back(p);
                    }
                    for (const auto& p : xyz) {
                        points.push_back(p);
                    }
                    auto dd = ConvexHull(points);
                } else {
                    std::vector<std::array<double, 3>> points;
                    for (size_t j = lastind; j < xyz.size(); j++) {
                        points.push_back(xyz[j]);
                    }
                    auto dd = ConvexHull(points, true);
                }
                lastind = xyz.size();
                // ConvexHull includes grid if no grid points on hull
                if (dd.simplices.min() >= gs2) {
                    break;
                }
            }
        }
        std::vector<double> travel_times;
        for (const auto& ti : t) {
            travel_times.push_back(ti);
        }
        return [xyz = std::move(xyz), travel_times = std::move(travel_times)](const double* p) -> double {
            return LinearNDInterpolator(xyz, travel_times)(p);
        };
    }
};
} // namespace acoular_cpp
#endif // _ENVIRONMENTS_H_