#include <iostream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include <string>

/**
 * @brief gsl库的demo
 * 
 * @note 输出结果：
    t = 0, y = 0 1
    t = 0.1, y = 0.0998334 0.995004
    t = 0.2, y = 0.198669 0.980067
    t = 0.3, y = 0.29552 0.955336
    t = 0.4, y = 0.389418 0.921061
    t = 0.5, y = 0.479426 0.877583
    t = 0.6, y = 0.564642 0.825336
    t = 0.7, y = 0.644218 0.764842
    t = 0.8, y = 0.717356 0.696707
    t = 0.9, y = 0.783327 0.62161
 */


int funcc(double t, const double y[], double f[], void *params)
{
    // 定义常微分方程
    double y1 = y[0];
    double y2 = y[1];
    double y1dot = y2;
    double y2dot = -y1;

    // 返回常微分方程的右侧
    f[0] = y1dot;
    f[1] = y2dot;

    return GSL_SUCCESS;
}

int main01()
{
    // 定义初始条件和时间步长
    double t = 0.0;
    double y[2] = {0.0, 1.0}; // 初始条件
    double h = 0.1;

    // 定义ODE求解器
    gsl_odeiv2_system sys = {funcc, NULL, 2, NULL};
    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

    // 进行数值积分
    for (int i = 0; i < 10; ++i)
    {
        double ti = i * h;
        int status = gsl_odeiv2_driver_apply(driver, &t, ti, y);
        if (status != GSL_SUCCESS)
        {
            std::cerr << "Error: gsl_odeiv2_driver_apply failed with status " << status << std::endl;
            break;
        }
        std::cout << "t = " << t << ", y = " << y[0] << " " << y[1] << std::endl;
    }

    // 释放ODE求解器
    gsl_odeiv2_driver_free(driver);

    return 0;
}


int main02()
{
    // 定义初始条件和时间步长
    double t = 0.0;
    double y[2] = {0.0, 1.0}; // 初始条件
    double h = 0.1;

    // 定义ODE求解器
    gsl_odeiv2_system sys = {funcc, NULL, 2, NULL};
    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rkf45, 1e-6, 1e-6, 0.0);

    // 进行数值积分
    for (int i = 0; i < 10; ++i)
    {
        double ti = i * h;
        int status = gsl_odeiv2_driver_apply(driver, &t, ti, y);
        if (status != GSL_SUCCESS)
        {
            std::cerr << "Error: gsl_odeiv2_driver_apply failed with status " << status << std::endl;
            break;
        }
        std::cout << "t = " << t << ", y = " << y[0] << " " << y[1] << std::endl;
    }

    // 释放ODE求解器
    gsl_odeiv2_driver_free(driver);

    return 0;
}

// 定义ODE系统的右手边函数
int func(double t, const double y[], double f[], void *params)
{
    double mu = *(double *)params;
    f[0] = y[1];
    f[1] = mu * (1 - y[0] * y[0]) * y[1] - y[0];
    return GSL_SUCCESS;
}

int main()
{
    double mu = 2.0;
    double y[2] = {1.0, 0.0};
    double t = 0.0;
    double t1 = 10.0;
    double h = 0.1;

    // 定义ODE系统的参数
    gsl_odeiv2_system sys = {func, NULL, 2, &mu};

    // 定义VODE积分器
    gsl_odeiv2_step *step = gsl_odeiv2_step_alloc(gsl_odeiv2_step_rk8pd, 2);
    gsl_odeiv2_control *control = gsl_odeiv2_control_y_new(1e-6, 0.0);
    gsl_odeiv2_evolve *evolve = gsl_odeiv2_evolve_alloc(2);

    // 进行数值积分
    while (t < t1)
    {
        int status = gsl_odeiv2_evolve_apply(evolve, control, step, &sys, &t, t1, &h, y);
        if (status != GSL_SUCCESS)
        {
            std::cerr << "Error: gsl_odeiv2_evolve_apply failed with status " << status << std::endl;
            break;
        }
        std::cout << "t = " << t << ", y = " << y[0] << " " << y[1] << std::endl;
    }

    // 释放VODE积分器
    gsl_odeiv2_evolve_free(evolve);
    gsl_odeiv2_control_free(control);
    gsl_odeiv2_step_free(step);

    return 0;
}