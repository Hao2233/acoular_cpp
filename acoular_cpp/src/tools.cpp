#include "tools.h"

using namespace std::complex_literals;

namespace acoular_cpp
{
std::vector<std::vector<double>> return_result(SamplesGenerator &source, int nmax, int num)
{
    std::vector<std::vector<double>> result;
    auto resulter = source.result(num);
    int count = 0;
    for (const auto &res : resulter)
    {
        result.push_back(res);
        count += res.size();
        if (nmax > 0 && count >= nmax)
        {
            break;
        }
    }
    if (nmax > 0 && count > nmax)
    {
        result.back().resize(result.back().size() - (count - nmax));
    }
    return result;
}

std::complex<double> spherical_hn1(int n, double z, bool derivativearccos)
{
    std::complex<double> jn = std::pow(-1.0 + 1.0i, n) * std::sqrt(0.5 / M_PI / z) * std::exp(std::complex<double>(0.0, 1.0) * z);
    std::complex<double> yn = std::pow(-1.0 + 1.0i, n) * std::sqrt(0.5 / M_PI / z) * std::exp(std::complex<double>(0.0, -1.0) * z);
    std::complex<double> hn = jn + 1.0i * yn;
    return hn;
}

std::vector<double> get_radiation_angles(std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition)
{
    std::vector<double> result(2);
    // 球谐函数的方向
    std::vector<double> direc(direction);
    double norm = 0;
    for (auto d : direc)
    {
        norm += d * d;
    }
    norm = std::sqrt(norm);
    for (auto &d : direc)
    {
        d /= norm;
    }
    // 麦克风到声源的距离
    std::vector<double> source_to_mic_vecs(3 * mpos.size());
    for (int i = 0; i < mpos.size(); i += 3)
    {
        source_to_mic_vecs[i] = mpos[i] - sourceposition[0];
        source_to_mic_vecs[i + 1] = mpos[i + 1] - sourceposition[1];
        source_to_mic_vecs[i + 2] = mpos[i + 2] - sourceposition[2];
    }
    source_to_mic_vecs[2] *= -1; // invert z-axis (acoular)    //-1
    // z-axis (acoular) -> y-axis (spherical)
    // y-axis (acoular) -> z-axis (spherical)
    // theta
    double ele = std::atan2(std::sqrt(source_to_mic_vecs[0] * source_to_mic_vecs[0] + source_to_mic_vecs[2] * source_to_mic_vecs[2]), source_to_mic_vecs[1]);
    ele += std::atan2(std::sqrt(direc[0] * direc[0] + direc[2] * direc[2]), direc[1]);
    ele += M_PI * 0.5; // convert from [-pi/2, pi/2] to [0,pi] range
    // phi
    double azi = std::atan2(source_to_mic_vecs[2], source_to_mic_vecs[0]);
    azi += std::atan2(direc[2], direc[0]);
    azi = std::fmod(azi, 2 * M_PI);
    result[0] = azi;
    result[1] = ele;
    return result;
}

std::vector<std::complex<double>> get_modes(int lOrder, std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition)
{
    std::vector<std::complex<double>> modes;
    std::vector<double> azi_ele = get_radiation_angles(direction, mpos, sourceposition);
    std::vector<double> azi(azi_ele.begin(), azi_ele.begin() + azi_ele.size() / 2);
    std::vector<double> ele(azi_ele.begin() + azi_ele.size() / 2, azi_ele.end());
    modes.resize(azi.size() * (lOrder + 1) * (lOrder + 1));
    int i = 0;
    for (int l = 0; l <= lOrder; l++)
    {
        for (int m = -l; m <= l; m++)
        {
            for (int j = 0; j < azi.size(); j++)
            {
                std::complex<double> sph = sph_harm(m, l, azi[j], ele[j]);
                if (m < 0)
                {
                    sph = std::conj(sph) * std::complex<double>(0, 1);
                }
                modes[i++] = sph;
            }
        }
    }
    return modes;
}

std::complex<double> sph_harm(int m, int l, double theta, double phi)
{
    double sqrt2 = std::sqrt(2.0);
    double norm = std::sqrt((2 * l + 1) / (4 * M_PI) * std::tgamma(l - m + 1) / std::tgamma(l + m + 1));
    double plm = 1.0;
    double x = std::cos(theta);
    double y = std::sin(theta);
    for (int i = 0; i < m; i++)
    {
        plm *= -sqrt2 * y;
        y = x * (2 * i + 1) * y - std::sqrt(i * (i + 1)) * plm;
        x = x * (2 * i + 1) - std::sqrt(i * (i + 1)) * plm;
        plm = plm / sqrt2;
    }
    double pmm = plm;
    if (m > 0)
    {
        double pmmp1 = x * std::sqrt(2 * m + 3) * pmm;
        double fact = std::sqrt(2 * m + 3);
        for (int i = m + 1; i < l + 1; i++)
        {
            double tmp = std::sqrt((2 * i + 1) / (i - m + 1) / (i + m)) * fact * y;
            fact = std::sqrt((2 * i + 3) / (i - m + 2) / (i + m + 1));
            pmm = pmmp1;
            pmmp1 = x * fact * pmm - tmp * plm;
            plm = pmm;
            y = x * fact * y - tmp * plm;
            x = x * (2 * i + 1) - std::sqrt(i * (i + 1)) * plm;
            plm = pmmp1 / std::sqrt((2 * i + 3));
        }
    }
    double azimuthal = m * phi;
    return std::complex<double>(norm * plm * std::cos(azimuthal), norm * plm * std::sin(azimuthal));
}

std::vector<double> barspectrum(std::vector<double> data, std::vector<double> fftfreqs, int num, bool bar, double xoffset)
{
    std::vector<double> flulist, plist, fc;
    if (num != 1 && num != 3)
    {
        std::cout << "Only octave and third-octave bands supported at this moment." << std::endl;
        return std::vector<double>();
    }
    std::vector<double> fcbase = {31.5, 40, 50, 63, 80, 100, 125, 160, 200, 250};
    for (int i = 0; i < 3; i++)
    {
        fc.insert(fc.end(), fcbase.begin(), fcbase.end());
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < fcbase.size(); j++)
        {
            fc.push_back(fcbase[j] * std::pow(10, i + 1));
        }
    }
    int ep = 1.0 / (2 * num);
    double f_low = fftfreqs[1] * std::pow(2, ep);
    double f_high = fftfreqs[fftfreqs.size() - 1] * std::pow(2, -ep);
    int i_low = 0, i_high = fc.size();
    for (int i = 0; i < fc.size(); i++)
    {
        if (fc[i] < f_low)
        {
            i_low = i;
        }
        if (fc[i] > f_high)
        {
            i_high = i;
            break;
        }
    }
    std::vector<double> fc_sub(fc.begin() + i_low, fc.begin() + i_high);
    std::vector<double> p = synthetic(data, fftfreqs, fc_sub, num);
    if (bar)
    {
        std::vector<double> flu;
        flu.push_back(fc[i_low] * std::pow(2, -ep));
        for (int i = i_low; i < i_high - 1; i++)
        {
            flu.push_back((fc[i] * std::pow(2, ep) + fc[i + 1] * std::pow(2, -ep)) / 2);
        }
        flu.push_back(fc[i_high - 1] * std::pow(2, ep));
        for (int i = 1; i < flu.size() - 1; i++)
        {
            flulist.push_back(std::pow(2, 2 * xoffset * ep) * flu[i]);
            flulist.push_back(std::pow(2, 2 * xoffset * ep) * flu[i]);
        }
        plist.insert(plist.end(), p.begin(), p.end());
        plist.insert(plist.end(), p.begin(), p.end());
    }
    else
    {
        flulist.insert(flulist.end(), fc_sub.begin(), fc_sub.end());
        plist.insert(plist.end(), p.begin(), p.end());
    }
    return flulist;
}

std::pair<std::vector<double>, std::vector<double>> bardata(std::vector<double> data, std::vector<double> fc, bool bar, double xoffset, int num, double masked)
{
    std::vector<double> flulist;
    std::vector<double> plist;
    double ep = 1.0 / (2.0 * num);
    if (bar)
    {
        // upper and lower band borders
        std::vector<double> flu(fc.size() + 1);
        flu[0] = fc[0] * std::pow(2, -ep);
        flu[fc.size()] = fc[fc.size() - 1] * std::pow(2, ep);
        for (int i = 1; i < fc.size(); i++)
        {
            flu[i] = (fc[i - 1] * std::pow(2, ep) + fc[i] * std::pow(2, -ep)) / 2.0;
        }
        // band borders as coordinates for bar plotting
        flulist.resize(flu.size() * 2 - 2);
        for (int i = 1; i < flu.size() - 1; i++)
        {
            flulist[2 * i - 2] = std::pow(2, xoffset / num) * flu[i];
            flulist[2 * i - 1] = std::pow(2, xoffset / num) * flu[i];
        }
        // sound pressures as list for bar plotting
        plist.resize(data.size() * (flu.size() - 2));
        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 1; j < flu.size() - 1; j++)
            {
                plist[i * (flu.size() - 2) + j - 1] = data[i];
            }
        }
    }
    else
    {
        flulist = fc;
        plist = data;
    }
    if (masked > -360.0)
    {
        for (int i = 0; i < plist.size(); i++)
        {
            if (plist[i] <= masked)
            {
                plist[i] = NAN;
            }
        }
    }
    return std::make_pair(flulist, plist);
}

void log(enum log_status sta,const std::string mes)
{
    // 判断是否存在log文件夹
    if (!std::filesystem::exists(std::filesystem::path("log")))
    {
        std::filesystem::create_directory(std::filesystem::path("log"));
    }

    // 判断log_status 类型
    std::string log_file_name;
    if (sta == ERROR)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        log_file_name = "log/" + std::to_string(1900 + ltm->tm_year) + "-" + 
            std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday) + ".err";
    }
    else
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        log_file_name = "log/" + std::to_string(1900 + ltm->tm_year) + "-" + 
            std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday) + ".log";
    }
}

} // namespace acoular_cpp