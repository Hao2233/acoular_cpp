#ifndef _ODE_H_
#define _ODE_H_

#include <vector>
#include <string>
#include <functional>

#include "gsl/gsl_odeiv2.h"

namespace acoular_cpp
{
/**
 * @brief ODE求解器 用于求解ODE
 * 
 */
class ODE {
private:
    gsl_odeiv2_system sys;  // ODE系统
    std::vector<double> y0; // 初始值
    std::vector<double> f_params;   // ODE函数参数
    std::vector<double> jac_params; // ODE雅克比矩阵参数
    std::string integrator_name;    // ODE求解器名称

public:
    /**
     * @brief 构造函数，用于初始化ODE求解器
     * 
     * @param func 函数指针，指向一个函数用于计算常微分方程的导数
     * @param jac 函数指针，指向一个函数用于计算雅克比矩阵
     * @param dimension ODE的维度
     */
    ODE(int (* func)(double t, const double y[], double dydt[], void * params),
        int (* jac)(double t, const double y[], double * dfdy, double dfdt[], void * params),
        size_t dimension);

    /**
     * @brief 设置ODE的初始值
     * 
     * @param y0 初始值
     */
    void set_initial_value(const std::vector<double> &y0);

    /**
     * @brief 设置ODE的函数参数
     * 
     * @param params 函数参数
     */
    void set_f_params(const std::vector<double> &params);

    /**
     * @brief 设置ODE的雅克比矩阵参数
     * 
     * @param params 雅克比矩阵参数
     */
    void set_jac_params(const std::vector<double> &params);

    /**
     * @brief 设置ODE的求解器
     * 
     * @param name 求解器名称
     */
    void set_integrator(const std::string &name = "vode");
    /**
     * @brief 求解ODE
     * 
     */
    void solve();
};
} // namespace acoular_cpp
#endif // _ODE_H_