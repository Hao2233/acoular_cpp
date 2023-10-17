#include "environments.h"

namespace acoular_cpp
{

std::vector<std::vector<double>> dist_mat(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos)
{
    int n = gpos.size();
    int m = mpos.size();
    std::vector<std::vector<double>> rm(n, std::vector<double>(m, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double dx = gpos[i][0] - mpos[j][0];
            double dy = gpos[i][1] - mpos[j][1];
            double dz = gpos[i][2] - mpos[j][2];
            rm[i][j] = sqrt(dx*dx + dy*dy + dz*dz);
        }
    }
    return rm;
}

std::vector<std::vector<double>> cartToCyl(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q) {
    int n = x.size();
    std::vector<std::vector<double>> xc(n, std::vector<double>(3, 0.0));
    for (int i = 0; i < n; i++) {
        xc[i][0] = x[i][0];
        xc[i][1] = x[i][1];
        xc[i][2] = x[i][2];
    }
    if (Q.size() > 0) {
        for (int i = 0; i < n; i++) {
            double x1 = xc[i][0];
            double y1 = xc[i][1];
            double z1 = xc[i][2];
            xc[i][0] = Q[0][0]*x1 + Q[0][1]*y1 + Q[0][2]*z1;
            xc[i][1] = Q[1][0]*x1 + Q[1][1]*y1 + Q[1][2]*z1;
            xc[i][2] = Q[2][0]*x1 + Q[2][1]*y1 + Q[2][2]*z1;
        }
    }
    std::vector<std::vector<double>> cyl(n, std::vector<double>(3, 0.0));
    for (int i = 0; i < n; i++) {
        double x1 = xc[i][0];
        double y1 = xc[i][1];
        double z1 = xc[i][2];
        double r = sqrt(x1*x1 + y1*y1);
        double phi = atan2(y1, x1);
        double z = z1;
        cyl[i][0] = phi;
        cyl[i][1] = r;
        cyl[i][2] = z;
    }
    return cyl;
}

std::vector<std::vector<double>> cylToCart(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q) {
    int n = x.size();
    std::vector<std::vector<double>> xc(n, std::vector<double>(3, 0.0));
    for (int i = 0; i < n; i++) {
        double r = x[i][1];
        double phi = x[i][0];
        double z = x[i][2];
        xc[i][0] = r*cos(phi);
        xc[i][1] = r*sin(phi);
        xc[i][2] = z;
    }
    if (Q.size() > 0) {
        for (int i = 0; i < n; i++) {
            double x1 = xc[i][0];
            double y1 = xc[i][1];
            double z1 = xc[i][2];
            xc[i][0] = Q[0][0]*x1 + Q[0][1]*y1 + Q[0][2]*z1;
            xc[i][1] = Q[1][0]*x1 + Q[1][1]*y1 + Q[1][2]*z1;
            xc[i][2] = Q[2][0]*x1 + Q[2][1]*y1 + Q[2][2]*z1;
        }
    }
    return xc;
}

std::vector<std::vector<double>> spiral_sphere(int N, double Om=2*M_PI, std::vector<double> b) {
    std::vector<std::vector<double>> xyz(N, std::vector<double>(3, 0.0));
    double o = 4*M_PI/Om;
    for (int i = 0; i < N; i++) {
        double h = -1 + 2*i/(N*o-1);
        double theta = acos(h);
        double phi = 0.0;
        if (i > 0) {
            phi = xyz[i-1][2] + 3.6/sqrt(N*o*(1-h*h));
            phi = fmod(phi, 2*M_PI);
        }
        xyz[i][0] = sin(theta) * cos(phi);
        xyz[i][1] = sin(theta) * sin(phi);
        xyz[i][2] = cos(theta);
    }
    std::vector<double> a = {xyz[0][0], xyz[0][1], xyz[0][2]};
    double norm_b = sqrt(b[0]*b[0] + b[1]*b[1] + b[2]*b[2]);
    std::vector<double> b_norm = {b[0]/norm_b, b[1]/norm_b, b[2]/norm_b};
    std::vector<double> ab = {a[0]-b_norm[0], a[1]-b_norm[1], a[2]-b_norm[2]};
    double norm_ab = sqrt(ab[0]*ab[0] + ab[1]*ab[1] + ab[2]*ab[2]);
    if (norm_ab < 1e-10) {
        return xyz;
    }
    std::vector<std::vector<double>> H(3, std::vector<double>(3, 0.0));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            H[i][j] = i == j ? 1.0 : 0.0;
            H[i][j] -= ab[i]*ab[j]/(norm_ab*norm_ab);
        }
    }
    std::vector<std::vector<double>> result(N, std::vector<double>(3, 0.0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                result[i][j] += H[j][k] * xyz[i][k];
            }
        }
    }
    return result;
}

std::vector<double> norm(std::vector<std::vector<double>> x, double ord, int axis, bool keepdims) {
    int m = x.size();
    int n = x[0].size();
    std::vector<double> result;
    if (axis == -1) {
        double sum = 0.0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum += pow(abs(x[i][j]), ord);
            }
        }
        result.push_back(pow(sum, 1.0 / ord));
    } else if (axis == 0) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int i = 0; i < m; i++) {
                sum += pow(abs(x[i][j]), ord);
            }
            result.push_back(pow(sum, 1.0 / ord));
        }
    } else if (axis == 1) {
        for (int i = 0; i < m; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += pow(abs(x[i][j]), ord);
            }
            result.push_back(pow(sum, 1.0 / ord));
        }
    }
    return result;
}

double norm(std::vector<std::vector<double>> x, double ord) {
    int m = x.size();
    int n = x[0].size();
    double sum = 0.0;
    if (ord == 1) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum += std::abs(x[i][j]);
            }
        }
    } else if (ord == 2) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum += std::pow(x[i][j], 2);
            }
        }
        sum = std::sqrt(sum);
    } else {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
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
    if (ord == 1) {
        for (int i = 0; i < n; i++) {
            sum += std::abs(x[i]);
        }
    } else if (ord == 2) {
        for (int i = 0; i < n; i++) {
            sum += std::pow(x[i], 2);
        }
        sum = std::sqrt(sum);
    } else {
        for (int i = 0; i < n; i++) {
            sum += std::pow(std::abs(x[i]), ord);
        }
        sum = std::pow(sum, 1.0 / ord);
    }
    return sum;
}

std::string Environment::get_digest() {
    return std::to_string(c);
}

std::vector<std::vector<double>> Environment::r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos) {
    int n = gpos.size();
    int m = mpos.size();
    std::vector<std::vector<double>> rm(n, std::vector<double>(m, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double dx = gpos[i][0] - mpos[j][0];
            double dy = gpos[i][1] - mpos[j][1];
            double dz = gpos[i][2] - mpos[j][2];
            rm[i][j] = sqrt(dx*dx + dy*dy + dz*dz);
        }
    }
    if (m == 1) {
        std::vector<double> rm1(n, 0.0);
        for (int i = 0; i < n; i++) {
            rm1[i] = rm[i][0];
        }
        return {rm1};
    }
    return rm;
}

std::tuple<std::vector<double>, std::vector<std::vector<double>>> SlotJet::v(std::vector<double> xx) {
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
    if (h1 < 0.0) {
        Ux = v0;
        Udx = 0.0;
        Udy = 0.0;
    } else {
        Ux = v0 * exp(-h1 * h1 / (2 * x1 * x1));
        Udx = (h1 * h1 / (x * x1 * x1) - sqrt(M_PI) * 0.5 * h1 / (x * x1)) * Ux;
        Udy = -copysign(1.0, y) * h1 * Ux / (x1 * x1);
    }

    std::vector<std::vector<double>> dU = {{Udx, 0.0, 0.0}, {Udy, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    std::vector<std::vector<double>> R = {{flow_norm[0], yy[0], zz[0]}, {flow_norm[1], yy[1], zz[1]}, {flow_norm[2], yy[2], zz[2]}};

    std::vector<double> velocity = {Ux, 0.0, 0.0};
    std::vector<std::vector<double>> jacobian = {{Udx, 0.0, 0.0}, {Udy, 0.0, 0.0}, {0.0, 0.0, 0.0}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            velocity[i] += R[i][j] * xx1[j];
            for (int k = 0; k < 3; k++) {
                jacobian[i][j] += R[i][k] * dU[k][j];
            }
        }
    }

    return make_tuple(velocity, jacobian);
}

std::tuple<std::vector<double>, std::vector<std::vector<double>>> OpenJet::v(std::vector<double> xx)  {
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


} // namespace acoular_cpp