#include "ode.h"

// GSL 库
#include "gsl/gsl_errno.h"
#include "gsl/gsl_odeiv2.h"

namespace acoular_cpp
{
void ode::set_initial_value(const std::vector<double> &y0, double t0)
{
    if (y0.size() == 1)
    {
        y = {y0[0]};
    }
    else
    {
        y = y0;
    }
    t = t0;
}

void ode::set_f_params(const std::vector<double> &params)
{
    f_params = params;
}

void ode::set_jac_params(const std::vector<double> &params)
{
    jac_params = params;
}

void ode::set_integrator(const std::string &name)
{
    if(name.empty())
    {
        return_code = 1;
        std::clog << "ode::set_integrator: name is empty" << std::endl;
        log(log_status::WARNING, "ode::set_integrator: name is empty");
        return;
    }
    if(name == "vode")
    {
        
    }
    else
    {
        return_code = 1;
        std::clog << "ode::set_integrator: 其他暂时没有写" << std::endl;
        log(log_status::WARNING, "ode::set_integrator: 其他暂时没有写");
        return;
    }
}

double ode::integrate(double t1, bool step, bool relax)
{
}

void ode::set_solout(std::function<int(double, const std::vector<double> &)> solout)
{


}

bool ode::successful()
{
    // TODO: 无实现
    return bool();
}

int ode::get_return_code()
{
    return return_code;
}

int ode::func(double t, const double y[], double f[], void *params)
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

} // namespace acoular_cpp
