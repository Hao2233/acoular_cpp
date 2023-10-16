#include "grids.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace acoular_cpp
{

Polygon::Polygon(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("x和y的长度必须相等");
    }
    x_ = x;
    y_ = y;
    // 如果多边形是开放的，则将其闭合
    double x1 = x[0], y1 = y[0];
    double xn = x[x.size() - 1], yn = y[y.size() - 1];
    if (x1 != xn || y1 != yn) {
        x_.push_back(x1);
        y_.push_back(y1);
    }
    // 如果多边形是顺时针的，则将其逆时针
    if (det(x_, y_) < 0) {
        std::reverse(x_.begin(), x_.end());
        std::reverse(y_.begin(), y_.end());
    }
}

double Polygon::is_inside(double xpoint, double ypoint, double smalld) const {
    // 检查x和y的长度是否相等
    if (x_.size() != y_.size()) {
        throw std::invalid_argument("x和y的长度必须相等");
    }
    // 如果snear = True：距离最近的边 < 最近的顶点
    // 如果snear = False：距离最近的顶点 < 最近的边
    bool snear = false;
    // 初始化数组
    double mindst = std::numeric_limits<double>::infinity();
    int j = -1;
    std::vector<double> x = x_;
    std::vector<double> y = y_;
    int n = x.size() - 1;  // 定义多边形的边数/顶点数
    // 循环遍历定义多边形的每条边
    for (int i = 0; i < n; i++) {
        double d = std::numeric_limits<double>::infinity();
        // 边的起点坐标为 (x1, y1)
        // 边的终点坐标为 (x2, y2)
        // 点的坐标为 (xpoint, ypoint)
        double x1 = x[i];
        double y1 = y[i];
        double x21 = x[i + 1] - x1;
        double y21 = y[i + 1] - y1;
        double x1p = x1 - xpoint;
        double y1p = y1 - ypoint;
        // 无限直线上的点的坐标为
        //     x = x1 + t * (x1 - x2)
        //     y = y1 + t * (y1 - y2)
        // 其中
        //     t = 0    时在 (x1, y1)
        //     t = 1    时在 (x2, y2)
        // 找到通过 (xpoint, ypoint) 的法线与无限直线相交的位置
        double t = -(x1p * x21 + y1p * y21) / (x21 * x21 + y21 * y21);
        bool tlt0 = t < 0;
        bool tle1 = (0 <= t) && (t <= 1);
        // 法线与边相交
        d = ((x1p + t * x21) * (x1p + t * x21) +
                (y1p + t * y21) * (y1p + t * y21));
        // 法线不与边相交
        // 点最靠近顶点 (x1, y1)
        // 计算到该顶点的距离的平方
        if (tlt0) {
            d = x1p * x1p + y1p * y1p;
        }
        // 存储距离
        if (d < mindst) {
            mindst = d;
            j = i;
            // 点最靠近 (x1, y1) 而不是其他任何顶点或边
            snear = false;
            // 点最靠近该边而不是其他任何边或顶点
            if (tle1) {
                snear = true;
            }
        }
    }
    if (j == -1) {
        throw std::invalid_argument("计算距离时出错");
    }
    mindst = sqrt(mindst);
    // 点最靠近其最近的顶点而不是最近的边，检查最近的顶点是否凹
    // 如果最近的顶点是凹的，则点在多边形内，否则点在多边形外
    int jo = j - 1;
    if (j == 0) {
        jo = n - 1;
    }
    double area = det({x[j + 1], x[j], x[jo]}, {y[j + 1], y[j], y[jo - 1]});
    if (!snear) {
        mindst = copysign(mindst, area);
    } else {
        // 点最靠近其最近的边而不是最近的顶点，检查点在该边的左侧还是右侧
        // 如果点在边的左侧，则点在多边形内，否则点在多边形外
        area = det({x[j], x[j + 1], xpoint}, {y[j], y[j + 1], ypoint});
        mindst = copysign(mindst, area);
    }
    // 点在多边形的边上
    if (fabs(mindst) < smalld) {
        mindst = 0;
    }
    return mindst;
}

double Polygon::det(const std::vector<double>& x, const std::vector<double>& y) const {
    double det = 0;
    for (int i = 0; i < x.size(); i++) {
        int j = (i + 1) % x.size();
        det += x[i] * y[j] - x[j] * y[i];
    }
    return det;
}

std::tuple<Eigen::ArrayXi, Eigen::ArrayXi> Grid::subdomain(const Grid& grid, const Sector& sector) const {
    

}



} // namespace acoular_cpp
