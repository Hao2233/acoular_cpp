#ifndef _ODE_H_
#define _ODE_H_

#include <vector>
#include <string>
#include <functional>

#include "tools.h"

namespace acoular_cpp
{
/**
 * @brief ode类用于求解常微分方程
 *
 */
class ode
{
public:
    /**
     * @brief 构造函数
     *
     * @param f 常微分方程右端函数
     * @param jac 右端函数的雅可比矩阵，可选
     */
    ode(std::function<void(double, const std::vector<double> &, std::vector<double> &)> f,
        std::function<void(double, const std::vector<double> &, std::vector<double> &)> jac = nullptr)
        : stiff(0), f(f), jac(jac), f_params(), jac_params(), y() {}

    std::vector<double> y; ///< 当前时间步长的解向量
    double t;              ///< 当前时间

    /**
     * @brief 设置初值
     *
     * @param y0 初值向量
     * @param t0 初值时间，默认为0
     */
    void set_initial_value(const std::vector<double> &y0, double t0 = 0.0);

    /**
     * @brief 设置右端函数的参数
     *
     * @param params 参数向量
     */
    void set_f_params(const std::vector<double> &params);

    /**
     * @brief 设置右端函数的雅可比矩阵的参数
     *
     * @param params 参数向量
     */
    void set_jac_params(const std::vector<double> &params);

    /**
     * @brief 设置积分器
     *
     * @param name 积分器名称
     */
    void set_integrator(const std::string &name);

    /**
     * @brief 求解常微分方程
     *
     * @param t1 终止时间
     * @param step 是否进行步进
     * @param relax 是否进行松弛
     * @return double 返回终止时间的解
     */
    double integrate(double t1, bool step = false, bool relax = false);

    /**
     * @brief 设置解的输出函数
     *
     * @param solout 解的输出函数
     */
    void set_solout(std::function<int(double, const std::vector<double> &)> solout);

    /**
     * @brief 判断求解是否成功
     *
     * @return true 成功
     * @return false 失败
     */
    bool successful();

    /**
     * @brief 获取返回码
     *
     * @return int 返回码
     */
    int get_return_code();

private:
    int stiff;                                                                           ///< 是否为刚性方程
    std::function<void(double, const std::vector<double> &, std::vector<double> &)> f;   ///< 常微分方程右端函数
    std::function<void(double, const std::vector<double> &, std::vector<double> &)> jac; ///< 右端函数的雅可比矩阵
    std::vector<double> f_params;                                                        ///< 右端函数的参数
    std::vector<double> jac_params;                                                      ///< 右端函数的雅可比矩阵的参数
    int return_code = 0;                                                                 ///< 返回码 
    std::string integrator_name = "vode";                                                ///< 积分器名称,默认为vode
    int func(double t, const double y[], double f[], void *params);                     ///< GSL库的常微分方程右端函数

};
} // namespace acoular_cpp
#endif // _ODE_H_