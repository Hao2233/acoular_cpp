# tools 文件

## 1. python代码介绍

该模块是aouclar库中的tools模块，提供一些用于声学信号处理的工具函数，包括：

`def return_result(source, nmax=-1, num=128)` : 这个函数名为`return_result`，它的作用是从一个`SamplesGenerator`对象中收集输出并返回一个包含所有数据的数组。这个函数有三个参数：`source`是一个`SamplesGenerator`对象，`nmax`是一个整数，用于设置最大输出样本数，`num`是一个整数，用于定义获取的块的大小。函数返回一个包含所有数据的浮点数数组，其形状为`样本数，source.numchannels`。

函数是`tools.py`文件中的一个函数，名为`return_result`。该函数从一个生成器中收集输出，并返回一个包含所有数据的组装数组。

该函数有三个参数：`source`、`nmax`和`num`。`source`是一个`SamplesGenerator`或派生对象，表示数据源。`nmax`是一个整数，用于设置最大输出样本数（数组的第一维）。如果设置为-1（默认值），则收集样本直到生成器停止。`num`是一个整数，定义要获取的块的大小，默认为128。

该函数首先使用`source.result(num)`方法获取一个生成器对象`resulter`。然后，它使用一个生成器表达式`(_.copy() for _ in resulter)`创建一个新的生成器对象`resulter`，该对象返回`resulter`生成器中的每个块的副本。接下来，函数使用`zip`函数将一个范围对象和`resulter`生成器对象打包在一起，以便在循环中同时迭代它们。如果`nmax`大于0，则函数计算要收集的块数`nblocks`，并使用`concatenate`函数将所有块连接起来。最后，函数返回一个包含所有数据的数组。


`def spherical_hn1(n,z,derivativearccos=False):` : 这个函数名为`spherical_hn1`，它的作用是计算球形Hankel函数。这个函数有三个参数：`n`是一个整数，`z`是一个浮点数，`derivativearccos`是一个布尔值，用于设置是否计算导数。函数返回一个浮点数，表示球形Hankel函数的值。

`def get_radiation_angles(direction,mpos, sourceposition):` : 这个函数的作用是计算麦克风和声源之间的方位角和俯仰角。它需要输入麦克风的位置、声源的位置和声源的方向，然后返回每个麦克风和声源之间的方位角和俯仰角。


`def get_modes(lOrder, direction, mpos , sourceposition = array([0,0,0])):` : get_modes函数是一个Python函数，定义在tools.py文件中。该函数计算了麦克风处的球谐辐射模式。它有四个参数：lOrder、direction、mpos和sourceposition。

lOrder参数是一个整数，指定球谐函数的最大阶数。direction参数是一个浮点数数组，指定球谐函数的方向。mpos参数是一个浮点数数组，指定麦克风的x、y、z位置。最后，sourceposition参数是一个浮点数数组，指定源的位置。

该函数首先使用get_radiation_angles函数计算源和麦克风之间的角度。然后，它使用零数组modes初始化一个数组，其中行数与角度数相同，列数为(lOrder+1)^2。函数然后循环遍历所有可能的l和m值，并使用sph_harm函数计算相应的球谐函数。如果m为负数，则函数取球谐函数的复共轭，并将其乘以虚数单位j。最终的球谐函数数组作为函数的输出返回。

`def barspectrum(data, fftfreqs, num = 3, bar = True, xoffset = 0.0):` : 这个活动选择是一个名为`barspectrum`的Python函数，定义在`tools.py`文件中。该函数用于合成频带值的谱数据，以便使用Matplotlib绘图命令绘制条形图。它有四个参数：`data`、`fftfreqs`、`num`、`bar`和`xoffset`。

`data`参数是一个浮点数数组，表示谱数据（以Pa为单位的声压），每个频率线一个值。`fftfreqs`参数是一个浮点数数组，表示FFT的离散频率。`num`参数是一个整数，控制所考虑的频带宽度，默认为3（三分之一倍频带）。`bar`参数是一个布尔值，确定是否返回类似条形图的曲线或正常的绘图。`xoffset`参数是一个浮点数，表示如果`bar`为True，则垂直线的偏移量。

该函数首先使用`fcbase`数组计算第三倍频带的首选中心频率。然后，它计算用于带宽计算的指数以及所选带和采样频率的最低和最高可能中心频率。函数然后使用`synthetic`函数和中心频率列表合成声压值。

如果`bar`为True，则函数计算上下频带边界和条形绘图的坐标。然后，它返回可绘制格式的下/上频带频率、相应的合成频带值以及评估的频带中心频率。如果`bar`为False，则函数返回中心频率和合成频带值。

`def bardata(data, fc, num=3, bar = True, xoffset = 0.0, masked = -360):` : 这个活动选择是`tools.py`文件中的一个函数，名为`bardata`。该函数返回数据，以便使用Matplotlib绘图命令绘制条形图。它有五个参数：`data`、`fc`、`num`、`bar`、`xoffset`和`masked`。

`data`参数是一个浮点数数组，表示谱数据。`fc`参数是一个浮点数数组，表示带中心频率。`num`参数是一个整数，控制所考虑的频带宽度，默认为3（三分之一倍频带）。`bar`参数是一个布尔值，确定是否返回类似条形图的曲线或正常的绘图。`xoffset`参数是一个浮点数，表示如果`bar`为True，则垂直线的偏移量。`masked`参数是一个浮点数，表示应屏蔽数据的值下限。

该函数首先使用`fcbase`数组计算第三倍频带的首选中心频率。然后，它计算用于带宽计算的指数以及所选带和采样频率的最低和最高可能中心频率。函数然后使用`synthetic`函数和中心频率列表合成声压值。

如果`bar`为True，则函数计算上下频带边界和条形绘图的坐标。然后，它返回可绘制格式的下/上频带频率、相应的合成频带值以及评估的频带中心频率。如果`bar`为False，则函数返回中心频率和合成频带值。

## 2. C++代码介绍

### `std::vector<std::vector<double>> return_result(SamplesGenerator& source, int nmax = -1, int num = 128);`
+ 作用 : 是从一个SamplesGenerator对象中收集输出并返回一个包含所有数据的数组
+ source : SamplesGenerator对象
+ nmax : 整数， 从source中收集的最大数据量，如果为-1，则收集所有数据
+ num : 整数， 用于定义获取的块的大小
+ 返回值 : 一个包含所有数据的数组

### `std::complex<double> spherical_hn1(int n, double z, bool derivativearccos=false);`
+ 作用：计算球形Hankel函数
+ n : 整数， 阶数
+ z : 复数， 自变量
+ derivativearccos : 布尔值， 是否计算arccos的导数
+ 返回值： 球形Hankel函数的值

### `std::vector<double> get_radiation_angles(std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition);`
+ 作用：是计算麦克风和声源之间的方位角和俯仰角
+ direction : 一个包含三个浮点数的数组， 表示声源的方向
+ mpos : 一个包含三个浮点数的数组， 表示麦克风的位置
+ sourceposition : 一个包含三个浮点数的数组， 表示声源的位置
+ 返回值： 一个包含两个浮点数的数组， 表示方位角和俯仰角

### `std::vector<std::complex<double>> get_modes(int lOrder, std::vector<double> direction, std::vector<double> mpos, std::vector<double> sourceposition = {0, 0, 0});`
+ 作用：计算球形波的模式
+ lOrder : 整数， 阶数
+ direction : 一个包含三个浮点数的数组， 表示声源的方向
+ mpos : 一个包含三个浮点数的数组， 表示麦克风的位置
+ sourceposition : 一个包含三个浮点数的数组， 表示声源的位置
+ 返回值： 一个包含复数的数组， 表示球形波的模式

### `std::complex<double> sph_harm(int m, int l, double theta, double phi);`
+ 作用： sph_harm函数是一个用于计算球谐函数的函数。球谐函数是一组定义在单位球面上的函数，它们在物理学、数学和工程学中具有广泛的应用。在声学中，球谐函数被用来描述声波在空间中的传播和辐射模式
+ m : 整数， 阶数
+ l : 整数， 阶数
+ theta : 浮点数， 极角
+ phi : 浮点数， 方位角
+ 返回值： 一个复数， 表示球谐函数的值

### `std::vector<double> barspectrum(std::vector<double> data, std::vector<double> fftfreqs, int num = 3, bool bar = true, double xoffset = 0.0);`
+ 用于计算频率带的下限和上限
+ num : 整数， 频率带的数量
+ fmin : 浮点数， 最低频率
+ fmax : 浮点数， 最高频率
+ 返回值： 一个包含两个浮点数的数组， 表示频率带的下限和上限

### `std::pair<std::vector<double>, std::vector<double>> bardata(std::vector<double> data, std::vector<double> fc, bool bar = true, double xoffset = 0.0, int num = 3, double masked = -360.0);`
+ 用于计算频率带的下限和上限以及相应的值
+ data : 一个包含复数的数组， 表示频率响应
+ fc : 一个包含浮点数的数组， 表示频率带的中心频率
+ bar : 布尔值， 是否计算频率带的下限和上限
+ xoffset : 浮点数， x轴的偏移量
+ num : 整数， 用于定义获取的块的大小
+ masked : 浮点数， 用于表示掩码的值
+ 返回值： 一个包含两个浮点数的数组， 表示频率带的下限和上限以及相应的值

### `void log(enum log_status sta,const std::string mes);`
+ 函数功能： 记录日志函数
+ sta：enum类型数据，日志类型，详细见 log_status.h文件
+ mes：string类型，需要记录的信息
+ 该函数会创建一个log文件夹，按照日期记录文件日志


## 3. 补充说明
