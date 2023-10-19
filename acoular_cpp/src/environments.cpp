#include "environments.h"

namespace acoular_cpp
{

std::vector<std::vector<double>> dist_mat(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos)
{
    int n = gpos.size();
    int m = mpos.size();
    std::vector<std::vector<double>> rm(n, std::vector<double>(m, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double dx = gpos[i][0] - mpos[j][0];
            double dy = gpos[i][1] - mpos[j][1];
            double dz = gpos[i][2] - mpos[j][2];
            rm[i][j] = sqrt(dx * dx + dy * dy + dz * dz);
        }
    }
    return rm;
}

std::vector<std::vector<double>> cartToCyl(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q)
{
    int n = x.size();
    std::vector<std::vector<double>> xc(n, std::vector<double>(3, 0.0));
    for (int i = 0; i < n; i++)
    {
        xc[i][0] = x[i][0];
        xc[i][1] = x[i][1];
        xc[i][2] = x[i][2];
    }
    if (Q.size() > 0)
    {
        for (int i = 0; i < n; i++)
        {
            double x1 = xc[i][0];
            double y1 = xc[i][1];
            double z1 = xc[i][2];
            xc[i][0] = Q[0][0] * x1 + Q[0][1] * y1 + Q[0][2] * z1;
            xc[i][1] = Q[1][0] * x1 + Q[1][1] * y1 + Q[1][2] * z1;
            xc[i][2] = Q[2][0] * x1 + Q[2][1] * y1 + Q[2][2] * z1;
        }
    }
    // TOD 这里有bug
    std::vector<std::vector<double>> cyl(n, std::vector<double>);
    for (int i = 0; i < n; i++)
    {
        double x1 = xc[i][0];
        double y1 = xc[i][1];
        double z1 = xc[i][2];
        double r = sqrt(x1 * x1 + y1 * y1);
        double phi = atan2(y1, x1);
        double z = z1;
        cyl[i][0] = phi;
        cyl[i][1] = r;
        cyl[i][2] = z;
    }
    return cyl;
}

std::vector<std::vector<double>> cylToCart(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q)
{
    int n = x.size();
    std::vector<std::vector<double>> xc(n, std::vector<double>(3, 0.0));
    for (int i = 0; i < n; i++)
    {
        double r = x[i][1];
        double phi = x[i][0];
        double z = x[i][2];
        xc[i][0] = r * cos(phi);
        xc[i][1] = r * sin(phi);
        xc[i][2] = z;
    }
    if (Q.size() > 0)
    {
        for (int i = 0; i < n; i++)
        {
            double x1 = xc[i][0];
            double y1 = xc[i][1];
            double z1 = xc[i][2];
            xc[i][0] = Q[0][0] * x1 + Q[0][1] * y1 + Q[0][2] * z1;
            xc[i][1] = Q[1][0] * x1 + Q[1][1] * y1 + Q[1][2] * z1;
            xc[i][2] = Q[2][0] * x1 + Q[2][1] * y1 + Q[2][2] * z1;
        }
    }
    return xc;
}

std::vector<std::vector<double>> spiral_sphere(int N, double Om, std::vector<double> b)
{
    std::vector<std::vector<double>> xyz(N, std::vector<double>(3, 0.0));
    double o = 4 * M_PI / Om;
    for (int i = 0; i < N; i++)
    {
        double h = -1 + 2 * i / (N * o - 1);
        double theta = acos(h);
        double phi = 0.0;
        if (i > 0)
        {
            phi = xyz[i - 1][2] + 3.6 / sqrt(N * o * (1 - h * h));
            phi = fmod(phi, 2 * M_PI);
        }
        xyz[i][0] = sin(theta) * cos(phi);
        xyz[i][1] = sin(theta) * sin(phi);
        xyz[i][2] = cos(theta);
    }
    std::vector<double> a = {xyz[0][0], xyz[0][1], xyz[0][2]};
    double norm_b = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
    std::vector<double> b_norm = {b[0] / norm_b, b[1] / norm_b, b[2] / norm_b};
    std::vector<double> ab = {a[0] - b_norm[0], a[1] - b_norm[1], a[2] - b_norm[2]};
    double norm_ab = sqrt(ab[0] * ab[0] + ab[1] * ab[1] + ab[2] * ab[2]);
    if (norm_ab < 1e-10)
    {
        return xyz;
    }
    std::vector<std::vector<double>> H(3, std::vector<double>(3, 0.0));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            H[i][j] = i == j ? 1.0 : 0.0;
            H[i][j] -= ab[i] * ab[j] / (norm_ab * norm_ab);
        }
    }
    std::vector<std::vector<double>> result(N, std::vector<double>(3, 0.0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                result[i][j] += H[j][k] * xyz[i][k];
            }
        }
    }
    return result;
}

std::vector<double> norm(std::vector<std::vector<double>> x, double ord, int axis, bool keepdims)
{
    int m = x.size();
    int n = x[0].size();
    std::vector<double> result;
    if (axis == -1)
    {
        double sum = 0.0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += pow(abs(x[i][j]), ord);
            }
        }
        result.push_back(pow(sum, 1.0 / ord));
    }
    else if (axis == 0)
    {
        for (int j = 0; j < n; j++)
        {
            double sum = 0.0;
            for (int i = 0; i < m; i++)
            {
                sum += pow(abs(x[i][j]), ord);
            }
            result.push_back(pow(sum, 1.0 / ord));
        }
    }
    else if (axis == 1)
    {
        for (int i = 0; i < m; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < n; j++)
            {
                sum += pow(abs(x[i][j]), ord);
            }
            result.push_back(pow(sum, 1.0 / ord));
        }
    }
    return result;
}

double norm(std::vector<std::vector<double>> x, double ord)
{
    int m = x.size();
    int n = x[0].size();
    double sum = 0.0;
    if (ord == 1)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += std::abs(x[i][j]);
            }
        }
    }
    else if (ord == 2)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += std::pow(x[i][j], 2);
            }
        }
        sum = std::sqrt(sum);
    }
    else
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += std::pow(std::abs(x[i][j]), ord);
            }
        }
        sum = std::pow(sum, 1.0 / ord);
    }
    return sum;
}

double norm(std::vector<double> x, double ord)
{
    int n = x.size();
    double sum = 0.0;
    if (ord == 1)
    {
        for (int i = 0; i < n; i++)
        {
            sum += std::abs(x[i]);
        }
    }
    else if (ord == 2)
    {
        for (int i = 0; i < n; i++)
        {
            sum += std::pow(x[i], 2);
        }
        sum = std::sqrt(sum);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            sum += std::pow(std::abs(x[i]), ord);
        }
        sum = std::pow(sum, 1.0 / ord);
    }
    return sum;
}

std::string Environment::get_digest()
{
    return std::to_string(c);
}

std::vector<std::vector<double>> Environment::r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos)
{
    int n = gpos.size();
    int m = mpos.size();
    std::vector<std::vector<double>> rm(n, std::vector<double>(m, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double dx = gpos[i][0] - mpos[j][0];
            double dy = gpos[i][1] - mpos[j][1];
            double dz = gpos[i][2] - mpos[j][2];
            rm[i][j] = sqrt(dx * dx + dy * dy + dz * dz);
        }
    }
    if (m == 1)
    {
        std::vector<double> rm1(n, 0.0);
        for (int i = 0; i < n; i++)
        {
            rm1[i] = rm[i][0];
        }
        return {rm1};
    }
    return rm;
}

std::tuple<std::vector<double>, std::vector<std::vector<double>>> SlotJet::v(std::vector<double> xx)
{
    std::vector<double> flow_norm(3);
    double flow_norm_val = sqrt(pow(flow[0], 2) + pow(flow[1], 2) + pow(flow[2], 2));
    flow_norm[0] = flow[0] / flow_norm_val;
    flow_norm[1] = flow[1] / flow_norm_val;
    flow_norm[2] = flow[2] / flow_norm_val;

    std::vector<double> plane_norm(3);
    double plane_norm_val = sqrt(pow(plane[0], 2) + pow(plane[1], 2) + pow(plane[2], 2));
    plane_norm[0] = plane[0] / plane_norm_val;
    plane_norm[1] = plane[1] / plane_norm_val;
    plane_norm[2] = plane[2] / plane_norm_val;

    std::vector<double> yy(3);
    yy[0] = -flow_norm[1] * plane_norm[2] + flow_norm[2] * plane_norm[1];
    yy[1] = -flow_norm[2] * plane_norm[0] + flow_norm[0] * plane_norm[2];
    yy[2] = -flow_norm[0] * plane_norm[1] + flow_norm[1] * plane_norm[0];

    std::vector<double> zz(3);
    zz[0] = flow_norm[1] * yy[2] - flow_norm[2] * yy[1];
    zz[1] = flow_norm[2] * yy[0] - flow_norm[0] * yy[2];
    zz[2] = flow_norm[0] * yy[1] - flow_norm[1] * yy[0];

    std::vector<double> xx1(3);
    xx1[0] = xx[0] - origin[0];
    xx1[1] = xx[1] - origin[1];
    xx1[2] = xx[2] - origin[2];

    double x = flow_norm[0] * xx1[0] + flow_norm[1] * xx1[1] + flow_norm[2] * xx1[2];
    double y = yy[0] * xx1[0] + yy[1] * xx1[1] + yy[2] * xx1[2];

    double x1 = 0.109 * x;
    double h1 = abs(y) + sqrt(M_PI) * 0.5 * x1 - 0.5 * B;

    double Ux, Udx, Udy;
    if (h1 < 0.0)
    {
        Ux = v0;
        Udx = 0.0;
        Udy = 0.0;
    }
    else
    {
        Ux = v0 * exp(-h1 * h1 / (2 * x1 * x1));
        Udx = (h1 * h1 / (x * x1 * x1) - sqrt(M_PI) * 0.5 * h1 / (x * x1)) * Ux;
        Udy = -copysign(1.0, y) * h1 * Ux / (x1 * x1);
    }

    std::vector<std::vector<double>> dU = {{Udx, 0.0, 0.0}, {Udy, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    std::vector<std::vector<double>> R = {{flow_norm[0], yy[0], zz[0]}, {flow_norm[1], yy[1], zz[1]}, {flow_norm[2], yy[2], zz[2]}};

    std::vector<double> velocity = {Ux, 0.0, 0.0};
    std::vector<std::vector<double>> jacobian = {{Udx, 0.0, 0.0}, {Udy, 0.0, 0.0}, {0.0, 0.0, 0.0}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            velocity[i] += R[i][j] * xx1[j];
            for (int k = 0; k < 3; k++)
            {
                jacobian[i][j] += R[i][k] * dU[k][j];
            }
        }
    }

    return make_tuple(velocity, jacobian);
}

std::tuple<std::vector<double>, std::vector<std::vector<double>>> OpenJet::v(std::vector<double> xx)
{
    double r = sqrt(pow(xx[0] - origin[0], 2) + pow(xx[1] - origin[1], 2) + pow(xx[2] - origin[2], 2));
    double U = v0 * pow(D / (D + 2 * r), 0.5);
    double Udx = -v0 * D * (xx[0] - origin[0]) / pow(D + 2 * r, 1.5);
    double Udy = -v0 * D * (xx[1] - origin[1]) / pow(D + 2 * r, 1.5);
    double Udz = -v0 * D * (xx[2] - origin[2]) / pow(D + 2 * r, 1.5);

    std::vector<double> velocity = {U, 0.0, 0.0};
    std::vector<std::vector<double>> jacobian = {{Udx, 0.0, 0.0}, {Udy, 0.0, 0.0}, {Udz, 0.0, 0.0}};

    return make_tuple(velocity, jacobian);
}

std::tuple<std::vector<double>, std::vector<std::vector<double>>> RotatingFlow::v(std::vector<double> xx)
{
    double x = xx[0] - origin[0];
    double y = xx[1] - origin[1];
    double z = xx[2] - origin[2];
    double r = sqrt(x * x + y * y + z * z);
    double omega = rpm * 2 * M_PI / 60;
    double U = v0 * (1 - pow(r, 2) * omega * omega / (4 * pow(v0, 2)));
    double V = v0 * x * omega / (2 * v0) * (1 - pow(r, 2) * omega * omega / (4 * pow(v0, 2))) - v0 * y * omega / (2 * v0);
    double W = v0 * x * omega / (2 * v0) + v0 * y * omega / (2 * v0) * (1 - pow(r, 2) * omega * omega / (4 * pow(v0, 2)));

    std::vector<double> velocity = {U, V, W};
    std::vector<std::vector<double>> jacobian = {{-2 * omega * x * y / pow(v0, 2), omega / v0 * (pow(x, 2) - pow(y, 2)), 0.0},
                                                    {-omega / v0 * (pow(x, 2) - pow(y, 2)), -2 * omega * x * y / pow(v0, 2), 0.0},
                                                    {0.0, 0.0, 0.0}};

    return make_tuple(velocity, jacobian);
}

GeneralFlowEnvironment::GeneralFlowEnvironment(Environment _ff, int _N, double _Om)
{
    ff = _ff;
    N = _N;
    Om = _Om;
}

std::vector<std::vector<double>> GeneralFlowEnvironment::_r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos)
{
    if (mpos.size() == 1 && mpos[0][0] == 0 && mpos[0][1] == 0 && mpos[0][2] == 0)
    {
        mpos = {{0, 0, 0}};
    }
    std::vector<std::vector<double>> gt(gpos.size(), std::vector<double>(mpos.size()));
    for (int micnum = 0; micnum < mpos.size(); micnum++)
    {
        auto x0 = mpos[micnum];
        auto x = x0;
        auto li = get_interpolator(gpos, x0);
        auto dist = li(x)[0];
    }
    if (gt[0].size() == 1)
    {
        std::vector<double> gt_1d(gt.size());
        for (int i = 0; i < gt.size(); i++)
        {
            gt_1d[i] = gt[i][0];
        }
        return {gt_1d};
    }
    return gt;
}

LinearNDInterpolator GeneralFlowEnvironment::get_interpolator(std::vector<std::vector<double>> roi, std::vector<double> x0)
{
    std::vector<std::vector<double>> xyz;
    std::vector<double> t;

    return LinearNDInterpolator();
}

LinearNDInterpolator GeneralFlowEnvironment::get_interpolator(std::vector<std::vector<double>> roi, std::vector<double> x0)
{
    double c = this->c;

    auto f1 = [&](double t, std::vector<double> y, std::function<std::tuple<std::vector<double>, std::vector<std::vector<double>>>(std::vector<double>)> v)
    {
        std::vector<double> x(y.begin(), y.begin() + 3);
        std::vector<double> s(y.begin() + 3, y.end());
        auto [vv, dv] = v(x);
        double sa = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
        std::vector<double> res(6);
        res[0] = c * s[0] / sa - vv[0];                                // time reversal
        res[1] = c * s[1] / sa - vv[1];                                // time reversal
        res[2] = c * s[2] / sa - vv[2];                                // time reversal
        res[3] = -s[0] * dv[0][0] - s[1] * dv[1][0] - s[2] * dv[2][0]; // time reversal
        res[4] = -s[0] * dv[0][1] - s[1] * dv[1][1] - s[2] * dv[2][1]; // time reversal
        res[5] = -s[0] * dv[0][2] - s[1] * dv[1][2] - s[2] * dv[2][2]; // time reversal
        return res;
    };

    // integration along a single ray
    auto fr = [&](std::vector<double> x0, std::vector<double> n0, double rmax,
                    double dt, std::function<std::tuple<std::vector<double>, std::vector<std::vector<double>>>(std::vector<double>)> v,
                    std::vector<std::vector<double>> &xyz, std::vector<double> &t)
    {
        /*
        std::vector<double> s0(3);
        for (int i = 0; i < 3; i++)
        {
            s0[i] = n0[i] / (c + v(x0) * n0[i]);
        }
        std::vector<double> y0(6);
        for (int i = 0; i < 3; i++)
        {
            y0[i] = x0[i];
            y0[i + 3] = s0[i];
        }
        double t0 = 0;
        while (t0 < rmax / c)
        {
            std::vector<double> y = y0;
            std::vector<double> k1 = f1(t0, y, v);
            for (int i = 0; i < 6; i++)
            {
                y[i] = y0[i] + k1[i] * dt / 2;
            }
            std::vector<double> k2 = f1(t0 + dt / 2, y, v);
            for (int i = 0; i < 6; i++)
            {
                y[i] = y0[i] + k2[i] * dt / 2;
            }
            std::vector<double> k3 = f1(t0 + dt / 2, y, v);
            for (int i = 0; i < 6; i++)
            {
                y[i] = y0[i] + k3[i] * dt;
            }
            std::vector<double> k4 = f1(t0 + dt, y, v);
            for (int i = 0; i < 6; i++)
            {
                y0[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) * dt / 6;
            }
            xyz.push_back(std::vector<double>(y0.begin(), y0.begin() + 3));
            t.push_back(t0);
            t0 += dt;
            if (sqrt(pow(y0[0] - x0[0], 2) + pow(y0[1] - x0[1], 2) + pow(y0[2] - x0[2], 2)) > rmax)
            {
                break;
            }
        }
        */

        std::vector<double> s0;
        for (int i = 0; i < n0.size(); i++)
        {
            s0.push_back(n0[i] / (c + std::get<0>(v(x0))[0] * n0[i]));
        }

        std::vector<double> y0;
        for (int i = 0; i < x0.size(); i++)
        {
            y0.push_back(x0[i]);
        }
        for (int i = 0; i < s0.size(); i++)
        {
            y0.push_back(s0[i]);
        }
    };

    int gs2 = roi[0].size();
    auto vv = ff.v();
    int NN = sqrt(this->N);
    std::vector<double> xe(3);
    for (int i = 0; i < 3; i++)
    {
        xe[i] = std::accumulate(roi[i].begin(), roi[i].end(), 0.0) / roi[i].size();
    }
    std::vector<std::vector<double>> roi_mat(roi[0].size(), std::vector<double>(3));
    for (int i = 0; i < roi[0].size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            roi_mat[i][j] = roi[j][i];
        }
    }
    std::vector<double> x0_vec = x0;
    std::vector<std::vector<double>> r(roi[0].size(), std::vector<double>(3));
    for (int i = 0; i < roi[0].size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            r[i][j] = x0_vec[j] - roi_mat[i][j];
        }
    }
    double rmax = 0;
    for (int i = 0; i < roi[0].size(); i++)
    {
        double dist = 0;
        for (int j = 0; j < 3; j++)
        {
            dist += pow(r[i][j], 2);
        }
        rmax = std::max(rmax, sqrt(dist));
    }
    std::vector<std::vector<double>> nv = spiral_sphere(this->N, this->Om, std::vector<double>(x0.begin(), x0.end()) - xe);
    double rstep = rmax / sqrt(this->N);
    rmax += rstep;
    double tstep = rstep / c;
    std::vector<std::vector<double>> xyz;
    std::vector<double> t;
    int lastind = 0;
    for (int i = 0; i < nv.size(); i++)
    {
        fr(x0, nv[i], rmax, tstep, vv, xyz, t);
        if (i && i % NN == 0)
        {
            if (!lastind)
            {
                std::vector<std::vector<double>> points = roi;
                points.insert(points.end(), xyz.begin(), xyz.end());
                auto [tri, hull] = ConvexHull(points);
            }
            else
            {
                std::vector<std::vector<double>> points(xyz.begin() + lastind, xyz.end());
                auto [tri, hull] = ConvexHull(points, true);
            }
            lastind = xyz.size();
            // ConvexHull includes grid if no grid points on hull
            if (*std::min_element(hull.begin(), hull.end()) >= gs2)
            {
                break;
            }
        }
    }
    return LinearNDInterpolator(xyz, t);
}

std::vector<double> GeneralFlowEnvironment::hstack(std::vector<double> a, std::vector<double> b)
{
    std::vector<double> c(a.size() + b.size());
    std::copy(a.begin(), a.end(), c.begin());
    std::copy(b.begin(), b.end(), c.begin() + a.size());
    return c;
}
} // namespace acoular_cpp