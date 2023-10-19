# grids 文件介绍

该文件的类包含：
1. Grid
2. RectGrid
3. RectGrid3D
4. ImportGrid
5. LineGrid
6. MergeGrid
7. Sector
8. RectSector
9. RectSector3D
10. CircSector
11. PolySector
12. ConvexSector
13. MultiSector

## 1. python类介绍

### Polygon 类

这个类是一个多边形对象，它有以下属性和方法：

属性：

+ x：一个包含多边形节点 x 坐标的数组。
+ y：一个包含多边形节点 y 坐标的数组。

方法：
+ __init__(self, x, y)：初始化多边形对象，输入参数为多边形节点的 x 和 y 坐标。
+ is_inside(self, xpoint, ypoint, smalld=1e-12)：检查点是否在多边形内部，输入参数为点的 x 和 y 坐标，以及一个小的浮点数 smalld，用于判断点是否在多边形边界上。输出参数为点到多边形的最近距离 mindst，如果 mindst < 0，则点在多边形外部；如果 mindst = 0，则点在多边形边界上；如果 mindst > 0，则点在多边形内部。


## 2. C++类介绍

## Polygon 类

这个类是一个多边形对象，用于描述阵元的位置，它有以下属性和方法：

成员变量：

+ std::vector<double> x：一个包含多边形节点 x 坐标的数组。
+ std::vector<double> y：一个包含多边形节点 y 坐标的数组。

成员函数：

`Polygon(const std::vector<double>& x, const std::vector<double>& y);`
+ 函数功能：构造函数，初始化多边形对象，
+ x: 输入参数为多边形节点的 x 坐标
+ y: 输入参数为多边形节点的 y 坐标。

`bool is_inside(double xpoint, double ypoint, double smalld=1e-12)`
+ 检查点是否在多边形内部，输入参数为点的 x 和 y 坐标，以及一个小的浮点数 smalld，用于判断点是否在多边形边界上。输出参数为点到多边形的最近距离 mindst，如果 mindst < 0，则点在多边形外部；如果 mindst = 0，则点在多边形边界上；如果 mindst > 0，则点在多边形内部。

+ double det(const std::vector<double>& x, const std::vector<double>& y) const; 计算行列式的值，输入参数为行列式的元素，输出参数为行列式的值。

## 3. 补充说明