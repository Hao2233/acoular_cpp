# environments 文件

## 1. python代码介绍

该文件主要是acoular库的环境

主要包含的类有：

1. Environment
2. UniformFlowEnvironment
3. GeneralFlowEnvironment
4. FlowField
5. OpenJet
6. RotatingFlow
7. SlotJet

### `def dist_mat(gpos,mpos):`

该函数用于计算3D空间中两组点之间的距离矩阵。它接受两个NumPy数组作为输入：gpos和mpos。gpos是一个3xN的数组，包含N个3D空间中的点，mpos是一个3xM的数组，包含M个3D空间中的点。该函数返回一个NxM的距离矩阵。

dist_mat函数使用嵌套循环来计算gpos中每个点与mpos中每个点之间的距离。它首先初始化一个空的NxM数组rm，用于存储距离。然后它循环遍历gpos中的每个点和mpos中的每个点，使用勾股定理计算两个点之间的欧几里得距离。距离然后存储在rm的相应元素中。

dist_mat函数使用Numba进行加速，Numba是Python的即时（JIT）编译器，可以加速数值计算。通过使用Numba，该函数可以利用编译代码的性能优势，而无需离开Python环境。

### `def cartToCyl(x, Q=identity(3)):`

该函数接受一个输入位置的笛卡尔坐标，并返回其柱坐标表示。输入位置首先被转换为一个修改的笛卡尔坐标系，该坐标系沿着正z方向流动。该函数还接受一个可选的正交变换矩阵Q，可以用于在将修改后的位置向量转换为柱坐标之前对其进行变换。

cartToCyl函数首先检查变换矩阵Q是否为单位矩阵。如果不是，则使用NumPy中的matmul函数将输入位置向量转换为修改后的位置向量。然后使用修改后的位置向量计算输入位置的柱坐标，使用NumPy中的arctan2和sqrt函数。

柱坐标作为一个NumPy数组返回，其形状为(3, nPoints)，其中nPoints是输入位置的数量。数组的第一个元素是方位角phi，第二个元素是径向距离r，第三个元素是高度z。

### `def cylToCart(x, Q=identity(3)):`
该函数接受一个输入位置的柱坐标，并返回其笛卡尔坐标表示。输入位置首先被转换为一个修改的笛卡尔坐标系，该坐标系沿着正z方向流动。该函数还接受一个可选的正交变换矩阵Q，可以用于在将修改后的位置向量转换为笛卡尔坐标之前对其进行变换。

cylToCart函数首先检查变换矩阵Q是否为单位矩阵。如果不是，则使用NumPy中的matmul函数将输入位置向量转换为修改后的位置向量。然后使用修改后的位置向量计算输入位置的笛卡尔坐标，使用NumPy中的sin和cos函数。

笛卡尔坐标作为一个NumPy数组返回，其形状为(3, nPoints)，其中nPoints是输入位置的数量。数组的第一个元素是x坐标，第二个元素是y坐标，第三个元素是z坐标。

### `def spiral_sphere(N, Om=2*pi, b=array((0, 0, 1))):    #change to 4*pi`

该函数是用于光线投射的内部辅助函数，返回一个数组，其中包含在一个球体的一部分上给出等分布方向的单位向量。该函数接受三个参数：N，它是要生成的方向数；Om，它是要覆盖的球体部分的立体角；b，它是要覆盖的球体部分的中心方向。

spiral_sphere函数首先计算球面坐标中方向分布的步长o。然后，使用步长和立体角Om在球面坐标中生成N个等分布方向。函数接着将方向转换为笛卡尔坐标，并在平面上镜像它们，以使中心方向b指向球体的中心。这是使用Householder矩阵进行镜像完成的。

spiral_sphere函数返回一个数组，其中包含在一个球体的一部分上给出等分布方向的单位向量。这些方向表示为一个2D NumPy数组，形状为(N, 3)，其中每行表示一个方向作为笛卡尔坐标中的单位向量。

spiral_sphere函数是用于光线投射的内部辅助函数，不打算由用户直接使用。它提供了一个有用的工具，用于生成一组方向，可用于在球体的一部分上进行光线投射。

### `def norm(x, ord=None, axis=None, keepdims=False):`

定义了一个名为 norm 的 Python 函数，用于计算输入数组 x 的矩阵或向量范数。该函数可以根据 ord 参数的值返回八种不同的矩阵范数或无限多种向量范数之一。

该函数接受四个参数：x，即输入数组；ord，即范数的阶数；axis，即沿着哪个轴或哪些轴计算范数；keepdims，即是否在输出中保留输入数组的维度。

norm 函数首先使用 asarray 函数将输入数组 x 转换为 NumPy 数组。如果输入数组不是 inexact 或 object_ 的子类，则将其转换为浮点数数组。然后，函数处理一些默认、简单、快速和常见的情况，例如计算 1-D 或 2-D 数组的 2-范数或 2-D 数组的 Frobenius 范数。如果 axis 参数不是 None，则将其规范化为元组。

如果 axis 参数为 None 或单个整数，则函数沿着指定的轴计算向量范数。该函数支持几种不同的向量范数，包括 2-范数、无穷范数、负无穷范数和零范数。如果 axis 参数是两个整数的元组，则函数计算由这两个轴指定的 2-D 子数组的矩阵范数。该函数支持几种不同的矩阵范数，包括 Frobenius 范数、核范数和最大范数。

norm 函数将输入数组的范数作为浮点数或 ndarray 返回。如果 keepdims 参数为 True，则规范化的轴将作为大小为一的维度保留在结果中。使用此选项，结果将正确地广播到原始输入数组。

### Environment 类介绍

该类表示一个简单的无流声学环境，并提供计算网格点位置和麦克风位置之间的传播时间（距离）的功能。该类有三个属性：digest、c和roi。

digest属性是一个内部标识符，它依赖于c属性。c属性是环境中声速的速度，默认为343 m/s。roi属性是感兴趣区域（ROI），对于大多数类型的环境来说都不需要。

Environment类有一个私有方法_get_digest，它返回类的摘要。该类还有一个公共方法_r，用于计算网格点位置和麦克风位置或原点之间的距离。该方法接受一个网格点位置的数组gpos和一个可选的麦克风位置的数组mpos。如果未给出mpos，则只考虑一个位于原点（0, 0, 0）的麦克风。该方法返回一个距离数组r，它是一个二维（N，M）浮点数组，其中N是网格点的数量，M是麦克风的数量。如果M为1，则只返回一个一维数组。

_r方法首先检查mpos是否为标量。如果是，则将mpos设置为一个在原点的一个麦克风的数组。然后，该方法使用dist_mat函数计算gpos和mpos之间的距离矩阵rm。如果rm只有一列，则将其转换为一维数组。最后，该方法返回距离数组rm。

### UniformFlowEnvironment 类介绍

该类表示一个具有均匀流的声学环境，并提供计算网格点位置和麦克风位置之间的传播时间（距离）的功能。该类有三个属性：ma、fdv和digest。

ma属性是马赫数，默认为0。fdv属性是给出流方向的单位向量，默认为沿x方向的流。digest属性是一个内部标识符，它依赖于c、ma和fdv属性。

UniformFlowEnvironment类有一个私有方法_r，用于计算网格点位置和麦克风位置或原点之间的虚拟距离。这些虚拟距离对应于声音的传播时间。该方法接受一个网格点位置的数组gpos和一个可选的麦克风位置的数组mpos。如果未给出mpos，则只考虑一个位于原点（0, 0, 0）的麦克风。该方法返回一个距离的二维数组，其中N是网格点的数量，M是麦克风的数量。如果M为1，则只返回一个一维数组。

_r方法首先检查mpos是否为标量。如果是，则将mpos设置为一个在原点的一个麦克风的数组。然后，该方法计算流方向的单位向量fdv和网格点位置与麦克风位置之间的虚拟距离rm。该方法使用马赫数ma来校正虚拟距离以考虑流的影响。最后，该方法将校正后的距离作为浮点数数组返回。

### FlowField 类介绍

该类是一个抽象基类，用于表示空间流场。它有一个属性：digest，它是一个返回空字符串的属性。

FlowField类有一个公共方法v，它将流场作为位置的函数提供。该方法实现了最简单的静止流体情况。该方法接受一个形状为(3,)的浮点数数组xx，表示要提供数据的流体位置。该方法返回一个元组，其中包含两个元素：给定位置处的速度向量和速度向量场的雅可比矩阵。

速度向量v被初始化为一个零数组。速度向量场的雅可比矩阵dv被初始化为一个3x3的零数组。然后，该方法返回v的负数和dv的负数。


### SlotJet 类介绍

该类提供了一个槽喷流的流场的解析近似，如Albertson等人（1950）所述。该类是FlowField抽象基类的子类，该基类提供了实现各种流场的框架。

SlotJet类有几个属性，用于定义槽喷流的属性。这些属性包括v0，它是喷嘴处的出口速度；origin，它是槽中心线上的一个点的位置；flow，它是槽喷流的单位流方向；plane，它是平行于槽中心面的单位向量；以及B，它是槽的宽度。这些属性具有默认值，但可以根据需要设置为特定值。

SlotJet类有一个digest属性，它是一个内部标识符，依赖于属性的值。该属性用于缓存计算结果，以便在属性未更改时可以重复使用。

SlotJet类有一个v方法，它将流场作为位置的函数提供。该方法仅针对flow方向的分量实现；捕获分量设置为零。该方法接受一个表示流体位置的一维向量xx，并返回一个元组，其中包含两个元素：给定位置处的速度向量和速度向量场的雅可比矩阵。

v方法首先将flow和plane向量归一化，以确保它们是单位向量。然后，它使用flow和plane的叉积计算全局坐标系的其他轴yy和zz。然后，该方法计算从槽出口平面到距离xx1和本地坐标系x和y。然后，该方法使用Albertson等人（1950）的公式计算核心喷流和剪切层的速度分量Ux、Udx和Udy。最后，该方法计算雅可比矩阵dU和旋转矩阵R，并返回速度向量和速度向量场的雅可比矩阵。

### OpenJet 类介绍

该类提供了一个开放式喷流的流场的解析近似，如Albertson等人（1950）所述。该类是FlowField抽象基类的子类，该基类提供了实现各种流场的框架。

该类具有三个属性：v0，它是喷嘴处的出口速度；origin，它是喷嘴中心的位置；以及D，它是喷嘴的直径。这些属性具有默认值，但可以根据需要设置为特定值。

该类有一个digest属性，它是一个内部标识符，依赖于属性的值。该属性用于缓存计算结果，以便在属性未更改时可以重复使用。

该类有一个v方法，它将流场作为位置的函数提供。该方法仅针对x方向的喷流实现；y和z分量设置为零。该方法接受一个表示流体位置的一维向量xx，并返回一个元组，其中包含两个元素：给定位置处的速度向量和速度向量场的雅可比矩阵。

v方法首先计算从喷嘴中心到给定位置的距离r。然后，它使用Albertson等人（1950）的公式计算给定位置处的速度U和速度导数Udx和Udy。最后，该方法返回速度向量和雅可比矩阵。

该类提供了一个有用的工具，用于模拟开放式喷流的流场。

### RotatingFlow 类介绍

该类提供了一个旋转流体的流场的解析近似，其中流体具有恒定的流量。该类是FlowField抽象基类的子类，该基类提供了实现各种流场的框架。

RotatingFlow类具有几个属性，用于定义旋转流体的属性。这些属性包括rpm，它是旋转速度（每分钟旋转次数）；v0，它是流速；origin，它是喷嘴中心的位置。这些属性具有默认值，但可以根据需要设置为特定值。

RotatingFlow类有一个digest属性，它是一个内部标识符，依赖于属性的值。该属性用于缓存计算结果，以便在属性未更改时可以重复使用。

RotatingFlow类有一个v方法，它将旋转流场作为位置的函数提供。该方法接受一个表示流体位置的一维向量xx，并返回一个元组，其中包含两个元素：给定位置处的速度向量和速度向量场的雅可比矩阵。

v方法首先计算从喷嘴中心到给定位置的距离x、y和z。然后，它使用rpm属性计算旋转速度omega。接下来，该方法使用旋转流体的恒定流量公式计算速度向量U、V和W。最后，该方法返回速度向量和雅可比矩阵。

RotatingFlow类提供了一个有用的工具，用于模拟具有恒定流量的旋转流体的流场。

### GeneralFlowEnvironment 类介绍

该类它表示具有通用流场的声学环境。它提供了计算在非均匀速度的通用流场中，网格点位置和麦克风位置之间的传播时间（距离）的功能。计算算法使用基于从每个麦克风位置投射的射线，并向时间反向跟踪的射线追踪方法。结果在由这些射线跨越的四面体网格内插值。

GeneralFlowEnvironment 类有几个属性，包括 ff、N 和 Om。ff 属性是 FlowField 类的一个实例，表示环境的流场。N 属性是每个立体角使用的射线数，Om 属性是算法中使用的最大立体角。该类还有一个内部标识符 digest，它取决于类的几个属性，包括 c、ff.digest、N 和 Om。

GeneralFlowEnvironment 类有几个方法，包括 _r 和 get_interpolator。_r 方法计算网格点位置和麦克风位置或原点之间的虚拟距离。这些虚拟距离对应于沿着通过介质追踪的射线的传播时间。该方法接受网格点位置数组 gpos 和麦克风位置数组 mpos 作为输入，并返回一个浮点数的二维数组中的距离数组。如果未给出 mpos，则仅考虑一个位于原点（0, 0, 0）的麦克风。

get_interpolator 方法获取一个 LinearNDInterpolator 对象，用于在由射线跨越的四面体网格内插值结果。该方法接受网格点位置数组 roi 和麦克风位置数组 x0 作为输入，并返回一个 LinearNDInterpolator 对象。LinearNDInterpolator 对象用于在由射线跨越的四面体网格内插值结果。


## 2. C++代码介绍

### `std::vector<std::vector<double>> dist_mat(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos);`
+ 作用： 计算两个点之间的距离
+ gpos： 一个包含三个浮点数的数组， 表示一个点的坐标
+ mpos： 一个包含三个浮点数的数组， 表示一个点的坐标
+ 返回值： 一个包含两个浮点数的数组， 表示距离矩阵
+ 说明：该函数使用两个二维向量gpos和mpos作为输入，这些向量包含了3D空间中的点。函数首先计算gpos和mpos的大小，然后初始化一个NxM的二维向量rm，用于存储距离矩阵。然后，函数使用嵌套循环遍历gpos中的每个点和mpos中的每个点，计算两个点之间的欧几里得距离，并将距离存储在rm的相应元素中。最后，函数返回距离矩阵rm。

### `std::vector<std::vector<double>> cartToCyl(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q);`
+ 作用： 将笛卡尔坐标转换为柱坐标
+ x： 一个包含三个浮点数的数组， 表示一个点的坐标
+ Q： 一个包含三个数组的数组， 表示一个旋转矩阵
+ 返回值： 一个包含三个浮点数的数组， 表示柱坐标
+ 说明：该函数使用两个二维向量x和Q作为输入，这些向量包含了笛卡尔坐标系中的点。函数首先计算x的大小，然后初始化一个Nx3的二维向量xc，用于存储修改后的笛卡尔坐标。然后，如果变换矩阵Q不为空，函数使用嵌套循环遍历xc中的每个点，将其乘以变换矩阵Q。接下来，函数使用嵌套循环遍历xc中的每个点，计算其柱坐标，并将其存储在Nx3的二维向量cyl中。最后，函数返回柱坐标向量cyl。

### `std::vector<std::vector<double>> cylToCart(std::vector<std::vector<double>> x, std::vector<std::vector<double>> Q);`
+ 作用： 将柱坐标转换为笛卡尔坐标
+ x： 一个包含三个浮点数的数组， 表示一个点的坐标
+ Q： 一个包含三个数组的数组， 表示一个旋转矩阵
+ 返回值： 一个包含三个浮点数的数组， 表示笛卡尔坐标
+ 说明：该函数接受一个输入位置的柱坐标，并返回其笛卡尔坐标表示。输入位置首先被转换为一个修改的笛卡尔坐标系，该坐标系沿着正z方向流动。该函数还接受一个可选的正交变换矩阵Q，可以用于在将修改后的位置向量转换为笛卡尔坐标之前对其进行变换。该函数使用两个二维向量x和Q作为输入，这些向量包含了柱坐标系中的点。函数首先计算x的大小，然后初始化一个Nx3的二维向量xc，用于存储修改后的笛卡尔坐标。然后，函数使用嵌套循环遍历x中的每个点，计算其笛卡尔坐标，并将其存储在Nx3的二维向量xc中。接下来，如果变换矩阵Q不为空，函数使用嵌套循环遍历xc中的每个点，将其乘以变换矩阵Q。最后，函数返回笛卡尔坐标向量xc。
  
### `std::vector<std::vector<double>> spiral_sphere(int N, double Om = 2 * M_PI, std::vector<double> b = {0.0, 0.0, 1.0});`
+ 作用： 用于光线投射的内部辅助函数，其中包含在一个球体的一部分上给出等分布方向的单位向量
+ N： 要生成的方向数
+ Om： 要覆盖的球体部分的立体角
+ b： 要覆盖的球体部分的中心方向
+ 函数返回一个二维向量，其中每行表示一个方向作为笛卡尔坐标中的单位向量。

###  `std::vector<double> norm(std::vector<std::vector<double>> x, double ord = 2, int axis = -1, bool keepdims = false);`
+ 函数作用： 用于计算输入数组X的矩阵
+ x：一个包含浮点数的二维数组，表示一个矩阵或向量
+ ord： 范数的阶数
+ axis： 范数计算的轴
+ keepdims： 如果为true，则保留轴上的尺寸
+ 返回值： 一个包含浮点数的一维数组，表示范数

### `double norm(std::vector<std::vector<double>> x, double ord = 2);`
+ 函数作用用于计算输入数组X的范数
+ x：一个包含浮点数的二维数组，表示一个矩阵或向量
+ ord：范数的阶数
+ 返回值：一个包含浮点数的一维数组，表示范数

### `double norm(std::vector<double> x, double ord = 2);`
+ 函数作用：用于计算输入数组x的范数
+ x：一个包含浮点数的一维数组，表示一个向量
+ ord：范数的阶数
+ 返回值：一个包含浮点数的一维数组，表示范数

### Environment 类介绍

环境类，用于计算声学环境中的声学参数

成员变量：
+ double c = 343.0; 声速，单位m/s
+ std::string digest; 用于缓存计算结果的哈希值
+ std::vector<std::vector<double>> roi; 区域 用于指定声学计算的区域

成员函数：

`std::string get_digest();`
+ 计算哈希值
+ 返回值：哈希值

`std::vector<std::vector<double>> r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos = {{0.0, 0.0, 0.0}});`

+ 作用： 计算网格点位置和麦克风位置之间的传播时间（距离）
+ gpos： 一个包含三个浮点数的数组， 表示网格点的坐标
+ mpos： 一个包含三个浮点数的数组， 表示麦克风的坐标
+ 返回值： 一个包含两个浮点数的数组， 表示距离矩阵

### UniformFlowEnvironment 类介绍

均匀流场环境类，用于描述均匀流场环境

成员变量：
+ double ma = 0.0; 马赫数 
+ std::vector<double> fdv = {1.0, 0.0, 0.0}; 流动方向向量
+ std::string digest; 哈希值

成员函数：

`std::vector<std::vector<double>> _r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos = {{0.0, 0.0, 0.0}});`

+ 函数功能 计算声源到各个测点的距离
+ gpos 测点位置
+ mpos 声源位置
+ return 各个测点到声源的距离
    
`std::vector<std::vector<double>> r(std::vector<std::vector<double>> gpos, std::vector<std::vector<double>> mpos = {{0.0, 0.0, 0.0}});`

+ 函数功能 计算声源到各个测点的距离
+ gpos 测点位置
+ mpos 声源位置
+ return 各个测点到声源的距离  

### FlowField 类介绍

流场类，提供流场速度场的计算

成员函数：

`virtual std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) = 0;`
+ 函数功能 计算流场速度场
+ xx 输入的流场位置坐标
+ return 返回速度场和速度梯度场

### SlotJet 类介绍

继承自FlowField类，表示一个具有槽口的气流场。

成员变量：
+ double v0 = 0.0; 初始速度
+ std::vector<double> origin = {0.0, 0.0, 0.0};  坐标原点
+ std::vector<double> flow = {1.0, 0.0, 0.0}; 气流方向
+ std::vector<double> plane = {0.0, 1.0, 0.0}; 平面法向量
+ double B = 0.2; 槽口宽度
+ std::string digest 哈希值

成员函数：

`std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override ;`

+ 函数功能：计算在给定位置的速度和雅可比矩阵。
+ xx 给定位置的坐标
+ return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 返回速度和雅可比矩阵

### OpenJet 类介绍

OpenJet类，继承自FlowField类，表示开放式喷流环境

成员变量：
+ double v0 = 0.0; 喷流速度
+ std::vector<double> origin = {0.0, 0.0, 0.0}; 喷流起点坐标
+ double D = 0.1; 喷流直径
+ std::string digest = ""; 哈希值

成员函数：

`std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override ;`
+ 函数功能：计算在给定位置的速度和雅可比矩阵。
+ xx 空间坐标
+ return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 速度和雅可比矩阵

### RotatingFlow 类介绍

旋转流场类，继承自FlowField类

成员变量：
+ double rpm = 0.0;转速，单位为rpm
+ double v0 = 0.0; 初始速度
+ std::vector<double> origin = {0.0, 0.0, 0.0};旋转中心坐标
+ std::string digest = ""; 哈希值

成员函数：  
`std::tuple<std::vector<double>, std::vector<std::vector<double>>> v(std::vector<double> xx) override ;`
+ 函数功能：计算在给定位置的速度和雅可比矩阵。
+ xx 空间坐标
+ return std::tuple<std::vector<double>, std::vector<std::vector<double>>> 速度和雅可比矩阵

### GeneralFlowEnvironment 类介绍


## 3. 补充说明