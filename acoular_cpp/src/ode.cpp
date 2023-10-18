#include "ode.h"

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
        // TODO : 无实现
    }

    double ode::integrate(double t1, bool step, bool relax)
    {
        // TODO : 无实现
        return double();
    }

    void ode::set_solout(std::function<int(double, const std::vector<double> &)> solout)
    {
        // TODO: 无实现
    }

    bool ode::successful()
    {
        // TODO: 无实现
        return bool();
    }

    int ode::get_return_code()
    {
        // TODO: 无实现
        return int();
    }

} // namespace acoular_cpp
