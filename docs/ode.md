# ODE 类

## 1. 简介

ode类的主要作用是用于求解常微分方程组。

同样属于acoular_cpp 命名空间

使用的文件主要是environments文件下面的GeneralFlowEnvironment类

## 2. 成员变量

+ std::vector<double> y;    当前时间步长的解向量
+ double t;                 当前时间
+ int stiff;                是否为刚性方程
+ std::function<void(double, const std::vector<double> &, std::vector<double> &)> f;    常微分方程右端函数
+ std::function<void(double, const std::vector<double> &, std::vector<double> &)> jac;  右端函数的雅可比矩阵
+ std::vector<double> f_params;                                                         右端函数的参数
+ std::vector<double> jac_params;                                                       右端函数的雅可比矩阵的参数
+ std::string integrator_name = "vode";                                                 积分器名称,默认为vode
在 Python scipy.integrate 模块中，vode 是一种数值方法，用于求解常微分方程组（ODE）。vode 是一种基于变步长的隐式 Adams 方法，它可以自适应地调整步长以保证数值稳定性和精度。vode 方法可以处理刚性和非刚性 ODE，并且可以处理具有不同时间尺度的多个物理过程的 ODE。
具体来说，vode 方法使用了一种称为“预测-校正”（predictor-corrector）的技术，它将当前时间点的解作为预测值，并使用一些内部计算来校正预测值。在校正过程中，vode 方法使用了一些称为“缩放因子”（scaling factors）的技术，以确保数值稳定性和精度。vode 方法还使用了一些称为“步长控制因子”（step control factors）的技术，以自适应地调整步长。
vode 方法是 ode 类的默认数值方法，因为它具有良好的数值稳定性和精度，并且可以处理各种类型的 ODE。但是，对于某些特定的 ODE，可能存在更好的数值方法。因此，ode 类提供了 set_integrator 方法，使用户可以选择不同的数值方法，并传递额外的参数以控制数值方法的行为。

## 3. 成员函数

+ ode(std::function<void(double, const std::vector<double> &, std::vector<double> &)> f,std::function<void(double, const std::vector<double> &, std::vector<double> &)> jac = nullptr); 
  + 函数功能： 构造函数
  + f： 常微方程右端函数
  + jac 右端函数的雅可比矩阵，可选
  
+ void set_initial_value(const std::vector<double> &y0, double t0 = 0.0); 
  + 函数功能：设置初值
  + y0： 初值向量
  + t0： 初值时间，默认为0

+ void set_f_params(const std::vector<double> &params);
  + 函数功能： 设置右端函数的参数
  + params： 参数向量

+ void set_jac_params(const std::vector<double> &params);
  + 函数功能： 设置右端函数的雅可比矩阵的参数
  + params： 参数向量

+ void set_integrator(const std::string &name);
  + 函数功能： 设置积分器
  + name： 积分器名称

+ double integrate(double t1, bool step = false, bool relax = false);
  + 函数功能： 求解常微方程
  + t1： 终止时间
  + step： 是否进行步进
  + relax： 是否进行松驰
  + 返回值： 返回终止时间

+ void set_solout(std::function<int(double, const std::vector<double> &)> solout); 
  + 函数功能： 设置解的输出函数
  + solout： 解的输出函数
  
+ bool successful();
  + 函数功能： 判断求解是否成功
  + 返回值：true（成功），false：失败
  
+ int get_return_code();
  + 函数功能：获取返回码
  + 返回值：int 返回码



## 4. 补充说明

主要使用gsl库中的ode求解器进行求解，具体的求解器可以参考gsl库中的ode文档