# trajectory

## 1. python代码介绍

这个类是用来描述一个轨迹的，它基于空间和时间上的离散点，通过样条插值计算出连续的轨迹。具体来说，它包含以下属性和方法：

属性：

- points：一个字典，将离散的时间点（键）与轨迹上对应的位置坐标（值）对应起来。
- interval：一个元组，表示轨迹的起始时间和结束时间。
- tck：一个元组，包含了样条插值所需的数据。

方法：

- location：给定一个或多个时间点，返回对应的位置坐标。
- traj：一个生成器，用于按照一定时间间隔生成轨迹上的位置坐标。

在这个类中，样条插值的计算是通过 scipy.interpolate 库中的 splprep 函数实现的。同时，该类还使用了 numpy 和 traits 库中的一些函数和类。


## 2. C++代码介绍

## 3. （C++）代码示例

```cpp
```

## 4. 补充

该类里面的splprep_()函数，splint_()函数的实现调用了Eiggen库中的函数，这个库是一个C++模板库，提供了线性代数、矩阵运算等功能。

Eigen库的官方网站：http://eigen.tuxfamily.org/index.php?title=Main_Page

Eigen库的安装：
    
```bash
Linux 下安装Eigen库：
    sudo apt-get install libeigen3-dev

macOS 下安装Eigen库：
    brew install eigen
```
