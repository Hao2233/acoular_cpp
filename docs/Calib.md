# Calib 

## 1. python代码介绍

python中的calib模块介绍
`Calib`类是一个用于多通道时间信号校准的容器，它实现了从`*.xml`格式的文件中加载校准数据的接口。

该类的属性：

1. `from_file`：要导入的`.xml`文件的名称。
2. `basename`：`.xml`文件的基本名称。只读/自动设置。
3. `num_mics`：校准数据中的麦克风数量，自动设置/从文件中读取。
4. `data`：校准因子的数组，自动设置/从文件中读取。

该类的方法

1. _get_digest() -> str：返回校准数据的哈希值。(私有方法，不需要调用）
2. _get_basename() -> str：返回`.xml`文件的基本名称。 (私有方法，不需要调用）
3. import_data()：从`*.xml`文件中加载校准数据。

## 2. C++代码介绍

C++中的Calib类是一个用于多通道时间信号校准的容器，它实现了从`*.xml`格式的文件中加载校准数据的接口。

该类的属性：
1. from_file : 要导入的`.xml`文件的名称。
2. basename : `.xml`文件的基本名称。只读/自动设置。
3. num_mics : 校准数据中的麦克风数量，自动设置/从文件中读取。
4. data : 校准因子的数组，自动设置/从文件中读取。
5. get_digest() : 返回校准数据的哈希值。

该类的方法：
1. Calib() : 构造函数, 从`*.xml`文件中加载校准数据。
2. get_basename() : 返回`.xml`文件的基本名称。
3. get_data() : 返回校准因子的数组。
4. get_num_mics() : 返回校准数据中的麦克风数量。

## 3. （C++）代码示例

```cpp
#include "Calib.h"

#include <iostream>

int main() {
    // 创建 Calib 对象并从文件中读取数据
    acoular_cpp::Calib calib("example_calib.xml");

    // 打印文件名和麦克风数量
    std::cout << "文件名称: " << calib.get_basename() << std::endl;
    std::cout << "麦克风数据: " << calib.get_num_mics() << std::endl;

    // 打印校准数据
    std::vector<double> data = calib.get_data();

    std::cout << "校准数据:" << std::endl;
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << std::endl;
    }

    return 0;
}
```
