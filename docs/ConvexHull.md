# ConvexHull 类

## 1. 简介

ConvexHull类用于计算二维点集的凸包

位于acoular_cpp命名空间中。

主要是给其他类使用的，用户一般不需要直接使用该类。

## 2. 成员变量

+ std::vector<std::vector<double>> points; /**< 存储点集的二维坐标 */
+ std::vector<int> vertices; /**< 存储凸包的顶点编号 */
+ std::vector<std::vector<int>> simplices; /**< 存储凸包的三角形面片 */

## 3. 成员函数

+ ConvexHull(const std::vector<std::vector<double>>& points); 构造函数，传入点集的二维坐标。
+ ConvexHull(std::vector<std::vector<double>> _points, std::vector<std::vector<double>> _values); 构造函数，传入点集的二维坐标和对应的值。
+ void _compute_hull(); 计算凸包。
+ double _cross(int i, int j, int k); 计算三个点的叉积。
+ std::vector<std::vector<int>> _compute_simplices(); 计算凸包的三角形面片。