#include "LinearNDInterpolator.h"

namespace acoular_cpp
{

LinearNDInterpolator::LinearNDInterpolator(std::vector<std::vector<double>> _points, std::vector<double> _values) {
    points = _points;
    values = _values;
}

double LinearNDInterpolator::operator()(std::vector<double> x)  {
    std::vector<int> indices = _find_indices(x);
    std::vector<double> dists = _find_dists(x, indices);
    std::vector<double> weights = _find_weights(dists);
    return _interpolate(indices, weights);
}

std::vector<int> LinearNDInterpolator::_find_indices(std::vector<double> x) {
    std::vector<int> indices(points.size());
    for (int i = 0; i < points.size(); i++) {
        indices[i] = i;
    }
    sort(indices.begin(), indices.end(), [&](int i, int j) {
        double dist_i = 0.0;
        double dist_j = 0.0;
        for (int k = 0; k < x.size(); k++) {
            dist_i += pow(x[k] - points[i][k], 2);
            dist_j += pow(x[k] - points[j][k], 2);
        }
        return dist_i < dist_j;
    });
    return indices;
}

std::vector<double> LinearNDInterpolator::_find_dists(std::vector<double> x, std::vector<int> indices) {
    std::vector<double> dists(points.size());
    for (int i = 0; i < points.size(); i++) {
        double dist = 0.0;
        for (int j = 0; j < x.size(); j++) {
            dist += pow(x[j] - points[indices[i]][j], 2);
        }
        dists[i] = sqrt(dist);
    }
    return dists;
}

std::vector<double> LinearNDInterpolator::_find_weights(std::vector<double> dists) {
    std::vector<double> weights(dists.size());
    double total_weight = 0.0;
    for (int i = 0; i < dists.size(); i++) {
        weights[i] = 1.0 / dists[i];
        total_weight += weights[i];
    }
    for (int i = 0; i < weights.size(); i++) {
        weights[i] /= total_weight;
    }
    return weights;
}

double LinearNDInterpolator::_interpolate(std::vector<int> indices, std::vector<double> weights) {
    double value = 0.0;
    for (int i = 0; i < indices.size(); i++) {
        value += weights[i] * values[indices[i]];
    }
    return value;
}
    
} // namespace acoular_cpp
