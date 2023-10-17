#include "spectra.h"

namespace acoular_cpp
{

std::vector<double> synthetic(std::vector<double> data, std::vector<double> freqs, std::vector<double> f, int num = 3) {
    std::vector<double> result;
    if (f.size() == 1) {
        double freq = f[0];
        int idx = std::distance(freqs.begin(), std::lower_bound(freqs.begin(), freqs.end(), freq));
        if (idx >= freqs.size() || freqs[idx] != freq) {
            return std::vector<double>();
        }
        result.push_back(data[idx]);
    } else {
        for (int i = 0; i < f.size(); i++) {
            double fc = f[i];
            double fl = fc * std::pow(2, -1.0 / (2 * num));
            double fu = fc * std::pow(2, 1.0 / (2 * num));
            double p = 0;
            for (int j = 0; j < freqs.size(); j++) {
                if (freqs[j] >= fl && freqs[j] <= fu) {
                    p += data[j];
                }
            }
            result.push_back(p);
        }
    }
    return result;
}
    
} // namespace acoular_cpp