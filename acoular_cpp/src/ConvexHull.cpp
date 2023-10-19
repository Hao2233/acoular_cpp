#include "ConvexHull.h"

namespace acoular_cpp
{
ConvexHull::ConvexHull(std::vector<std::vector<double>> _points)
{
    points = _points;
    _compute_hull();
}

ConvexHull::ConvexHull(std::vector<std::vector<double>> _points, std::vector<std::vector<double>> _values)
{
    points = _points;
    _compute_hull();
}

void ConvexHull::_compute_hull()
{
    int n_points = points.size();
    std::vector<int> indices(n_points);
    for (int i = 0; i < n_points; i++)
    {
        indices[i] = i;
    }
    sort(indices.begin(), indices.end(), [&](int i, int j)
            { return points[i][0] < points[j][0]; });
    std::vector<int> lower_hull;
    for (int i = 0; i < n_points; i++)
    {
        while (lower_hull.size() >= 2 && _cross(lower_hull[lower_hull.size() - 2], lower_hull[lower_hull.size() - 1], indices[i]) <= 0)
        {
            lower_hull.pop_back();
        }
        lower_hull.push_back(indices[i]);
    }
    std::vector<int> upper_hull;
    for (int i = n_points - 1; i >= 0; i--)
    {
        while (upper_hull.size() >= 2 && _cross(upper_hull[upper_hull.size() - 2], upper_hull[upper_hull.size() - 1], indices[i]) <= 0)
        {
            upper_hull.pop_back();
        }
        upper_hull.push_back(indices[i]);
    }
    vertices = lower_hull;
    vertices.insert(vertices.end(), upper_hull.begin() + 1, upper_hull.end() - 1);
    simplices = _compute_simplices();
}

double ConvexHull::_cross(int i, int j, int k)
{
    double x1 = points[j][0] - points[i][0];
    double y1 = points[j][1] - points[i][1];
    double x2 = points[k][0] - points[i][0];
    double y2 = points[k][1] - points[i][1];
    return x1 * y2 - x2 * y1;
}

std::vector<std::vector<int>> ConvexHull::_compute_simplices()
{
    std::vector<std::vector<int>> simplices;
    for (int i = 1; i < vertices.size() - 1; i++)
    {
        std::vector<int> simplex = {0, vertices[i], vertices[i + 1]};
        simplices.push_back(simplex);
    }
    return simplices;
}

} // namespace acoular_cpp
