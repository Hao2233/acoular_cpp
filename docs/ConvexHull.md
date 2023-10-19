# ConvexHull 类

## 1. 简介

ConvexHull类用于计算二维点集的凸包

位于acoular_cpp命名空间中。

主要是给其他类使用的，用户一般不需要直接使用该类。

## 2. 成员变量

+ std::vector<std::vector<double>> points; 存储点集的二维坐标
+ std::vector<int> vertices; 存储凸包的顶点编号
+ std::vector<std::vector<int>> simplices; 存储凸包的三角形面片

## 3. 成员函数

+ ConvexHull(const std::vector<std::vector<double>>& points); 
  + 构造函数，计算给定集的凸包
  + points给定的点集，每个元素为一个二维坐标
  
+ ConvexHull(std::vector<std::vector<double>> _points, std::vector<std::vector<double>> _values); 
  + 构造函数用于计算给定集的凸包
  + _points 给定的点集，每个元素是一个二维坐标点的vector
  + _values 给定的点集对应的值，每个元素是一个值的vector

+ void _compute_hull();
  + 函数功能：计算凸包

+ double _cross(int i, int j, int k);
  + 函数功能： 计算三个点组成的向量的叉积
  + i： 第一个点的编号
  + j： 第二个点的编号
  + k： 第三个点的编号
  + 返回值： 三个点组成的向量的叉积

+ std::vector<std::vector<int>> _compute_simplices(); 
  + 计算凸包的三角形面片
  + 返回值： 存储凸包的三角形面片的二维数组