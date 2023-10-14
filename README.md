# Acoular
Acoular is a Python module for acoustic beamforming that is distributed under the new BSD license. 

It is aimed at applications in acoustic testing. Multichannel data recorded by a microphone array can be processed and analyzed in order to generate mappings of sound source distributions. The maps (acoustic photographs) can then be used to locate sources of interest and to characterize them using their spectra. 

# Features
- covers several beamforming algorithms 
- different advanced deconvolution algorithms
- both time-domain and frequency-domain operation included
- 3D mapping possible
- application for stationary and for moving targets
- supports both scripting and graphical user interface
- efficient: intelligent caching, parallel computing with Numba
- easily extendible and well documented

# Dependencies
Acoular runs under Linux, Windows and MacOS, a Python 3.9, 3.8, 3.7 or 3.6 installation is needed with the Numpy, Scipy, Traits, scikit-learn, pytables, numba packages available. Matplotlib is recommended, but not necessary.

# 中文说明
Acoular是一个用于声波波束成像的Python模块，它在新的BSD许可下分发。

它旨在应用于声学测试。可以处理和分析由麦克风阵列记录的多通道数据，以生成声源分布的映射。然后可以使用这些映射（声学照片）来定位感兴趣的源并使用其频谱对其进行表征。

# 特征
- 覆盖几种波束成像算法
- 不同的高级去卷积算法
- 包括时域和频域操作
- 可以进行3D映射
- 适用于静止和移动目标
- 支持脚本和图形用户界面
- 高效：智能缓存，Numba并行计算
- 易于扩展和文档化
- 依赖项

# 依赖项
Acoular在Linux，Windows和MacOS下运行，需要Python 3.9，3.8，3.7或3.6安装，并可用Numpy，Scipy，Traits，scikit-learn，pytables，numba包。建议使用Matplotlib，但不是必需的。

# acoular_cpp

说明：acoular_cpp是acoular的C++版本，用于加速计算，目前只实现了一部分功能，后续会继续完善。