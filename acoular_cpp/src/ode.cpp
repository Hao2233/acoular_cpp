#include "ode.h"

#include <iostream>
#include <vector>
#include <cmath>

namespace acoular_cpp
{
ODE::ODE(int (* func)(double t, const double y[], double dydt[], void * params),
        int (* jac)(double t, const double y[], double * dfdy, double dfdt[], void * params),
        size_t dimension)
{
    sys.function = func;
    sys.jacobian = jac;
    sys.dimension = dimension;
    sys.params = nullptr;
}

void ODE::set_initial_value(const std::vector<double> &y0) {
    this->y0 = y0;
}

void ODE::set_f_params(const std::vector<double> &params) {
    this->f_params = params;
    sys.params = this->f_params.data();
}

void ODE::set_jac_params(const std::vector<double> &params) {
    this->jac_params = params;
}

void ODE::set_integrator(const std::string &name) {
    this->integrator_name = name;
}

void ODE::solve() {
    const gsl_odeiv2_step_type * T = gsl_odeiv2_step_rk8pd;
    gsl_odeiv2_step * s = gsl_odeiv2_step_alloc (T, sys.dimension);
    gsl_odeiv2_control * c = gsl_odeiv2_control_y_new (1e-6, 0.0);
    gsl_odeiv2_evolve * e = gsl_odeiv2_evolve_alloc (sys.dimension);

    double t = 0.0, t1 = 100.0;
    double h = 1e-6;
    double y[sys.dimension];
    for (size_t i = 0; i < sys.dimension; i++) {
        y[i] = y0[i];
    }

    while (t < t1)
    {
        int status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &t, t1, &h, y);

        if (status != GSL_SUCCESS)
            break;
    }

    gsl_odeiv2_evolve_free (e);
    gsl_odeiv2_control_free (c);
    gsl_odeiv2_step_free (s);
}
} // namespace acoular_cpp