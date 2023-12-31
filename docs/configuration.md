# configuration 文件

包含的类包括：Config

## 1. python代码介绍

这个类是Acoular软件包中的一个缓存类，用于处理打开和关闭“tables.File”对象。它提供了一些方法来打开和关闭缓存文件，获取文件名，获取打开的缓存文件以及关闭未引用的缓存文件。此外，它还提供了一些属性来跟踪缓存文件的状态，如繁忙状态和打开的文件列表。

### 属性

+ global_caching：全局定义Acoular类的缓存行为的标志，默认为“individual”。
+ _global_caching：Trait类型，定义了全局缓存行为的可选值。
+ h5library：全局定义用于读写.h5文件的包的标志，默认为“pytables”。
+ _h5library：Trait类型，定义了可选的.h5文件读写包。
+ cache_dir：定义包含Acoular缓存文件的目录的路径。
+ _cache_dir：字符串类型，定义了缓存目录的路径。
+ td_dir：定义包含可以由fileimport.py模块加载的文件的工作目录的路径。
+ _td_dir：字符串类型，定义了工作目录的路径。
+ use_traitsui：布尔类型，确定用户是否可以访问traitsui功能，默认为False。
+ _use_traitsui：布尔类型，定义了是否使用traitsui的标志。

### 方法

+ _get_global_caching()：获取global_caching属性的值。
+ _set_global_caching(globalCachingValue)：设置global_caching属性的值。
+ _get_h5library()：获取h5library属性的值。
+ _set_h5library(libraryName)：设置h5library属性的值。
+ _get_use_traitsui()：获取use_traitsui属性的值。
+ _set_use_traitsui(use_tui)：设置use_traitsui属性的值。
+ _assert_h5library()：检查是否安装了tables或h5py包，如果没有则引发ImportError。
+ _get_cache_dir()：获取cache_dir属性的值。
+ _set_cache_dir(cdir)：设置cache_dir属性的值。
+ _get_td_dir()：获取td_dir属性的值。
+ _set_td_dir(tddir)：设置td_dir属性的值。
+ __init__()：类的构造函数，初始化类的属性。
+ config：类的实例，实现了Acoular包的全局配置。

## 2. c++代码介绍

### 成员变量

+ GlobalCaching _global_caching; enum类型 全局缓存模式枚举
  + INDIVIDUAL  每个对象单独缓存
  + ALL         所有对象共享缓存
  + NONE        不使用缓存
  + READONLY    只读缓存
  + OVERWRITE   覆盖缓存

+ H5Library _h5library; enum枚举类型 HDF5库枚举 这里主要是python当中引入的解析HDF5文件所使用的库
  + PYTABLES PyTables库
  + H5PY h5py库

+ std::string _cache_dir; 缓存目录 
  
+ std::string _td_dir; 时间数据目录 

+ bool _use_traitsui; 是否使用TraitsUI 
  + true 是
  + false 否

### 成员函数

+ Config();
  + 函数功能： 构造函数，在python代码当中主要功能是查看HDF5库是否引入，这里暂时不做实现

+ GlobalCaching global_caching() const; 
  + 函数功能： 获取全局缓存模式。
  + 返回值： 全局缓存模式

+ void set_global_caching(GlobalCaching global_caching); 
  + 函数功能： 设置全局缓存模式。
  + global_caching： 全局缓存模式

+ H5Library h5library() const; 
  + 函数功能： 获取HDF5库
  + 返回值： HDF5库

+ void set_h5library(H5Library h5library); 
  + 函数功能： 设置HDF5库
  + h5library： HDF5库

+ std::string cache_dir() const; 
  + 函数功能： 获取缓存目录
  + 返回值： 缓存目录

+ void set_cache_dir(const std::string& cache_dir);
  + 函数功能： 设置缓存目录
  + cache_dir： 缓存目录

+ std::string td_dir() const; 
  + 函数功能： 获取时间数据目录
  + 返回值：时间数据目录

+ void set_td_dir(const std::string& td_dir);
  + 函数功能： 设置时间数据目录
  + td_dir： 时间数据目录

+ bool use_traitsui() const; 
  + 函数功能： 获取是否使用TraitsUI
  + 返回值： true 是，falase 否

+ void set_use_traitsui(bool use_traitsui); 
  + 函数功能：设置是否使用TraitsUI
  + use_traitsui： true 是，false 否

+ void _assert_h5library(); 
  + 函数功能：检查HDF5库是否可用
  + python代码这里主要是检查HDF5库是否引入，c++这里不做实现

## 3. 补充说明
