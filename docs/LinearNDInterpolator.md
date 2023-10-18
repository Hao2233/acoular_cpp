# LinearNDInterpolator 类 文档

## 1. 简介

主要是给environments文件中的GeneralFlowEnvironment类使用的，用于多维线性插值的类

位于：acoular_cpp 命名空间下

## 2. 成员变量

+ std::vector<std::vector<double>> points; /**< 插值点的坐标 */
+ std::vector<double> values; /**< 插值点的值 */

## 3. 成员函数

+ LinearNDInterpolator(std::vector<std::vector<double>> _points, std::vector<double> _values); 构造函数，初始化成员变量，参数分别为插值点的坐标和值
+ double operator()(std::vector<double> x); 重载()运算符，用于计算插值点的值，参数为插值点的坐标
+ std::vector<int> _find_indices(std::vector<double> x); 找到插值点的坐标在points中的索引，参数为插值点的坐标
+ std::vector<double> _find_dists(std::vector<double> x, std::vector<int> indices); 找到插值点的坐标与points中的坐标的距离，参数为插值点的坐标和索引
+ std::vector<double> _find_weights(std::vector<double> dists); 找到插值点的权重，参数为插值点的坐标与points中的坐标的距离
+ double _interpolate(std::vector<double> weights, std::vector<int> indices); 插值，参数为插值点的权重和索引