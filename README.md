
实验代码一共涉及三种基数估计算法：Linear Counting（LC）、HyperLogLog（HLL）以及K Minimum Values（KMV），这三种算法分别属于三类不同的基数估计算法。实验主要包含了对这三种算法进行参数推测、基数膨胀攻击以及基数缩减攻击的方案设计。

此外，实验均在只能进行黑盒测试的场景下展开，即对于指定的基数估计算法，不知道其具体实现，只能通过应用编程接口（API）对执行sketch的创建、插入元素以及计算基数等操作。

## 一、文件
### 1. 基本文件

- bitmap：位图的实现
- hash：实验使用哈希函数的相关实现
### 2. Linear Counting相关

- discounter_lc：LC算法基本实现
- lc_bt.cpp：推测LC使用的位图大小（假设桶的个数可以为任意值的情况）
- lc_bt_improve.cpp：推测LC使用的位图大小（假设桶的个数一定为2的指数倍的情况）
- lc_flat_s1.cpp：基数膨胀攻击
- lc_deflat.cpp：基数缩减攻击
### 3. HyperLogLog相关

- discounter_hll：HLL算法实现
- hll_infer_m.cpp：推测使用的桶的大小
- hll_inflation.cpp：基数膨胀攻击
- 基数缩减攻击：
   - 已有论文的复现：“HyperLogLog: Exponentially Bad in Adversarial Settings”文中的5.2.2小节中两种版本攻击的实现
      - hll_deflation_s1_v1.cpp：简单版本的实现
      - hll_deflation_s1_v2.cpp：复杂版本的实现
   - 我们提出的方案：hll_deflation.cpp
### 4. K Minimum Values相关

- discounter_km：KMV算法的基本实现代码
- km_infer_k.cpp：推测KMV使用的K值
- 基数膨胀攻击：
   - km_inflation.cpp：论文“On the Security of the K Minimum Values (KMV) Sketch ”中3.1小节中描述攻击的复现
   - 我们的方案：
      - km_inflation2.cpp
      - km_inflation3.cpp：km_inflation2.cpp的改进，利用了km_inflation.cpp的代码，减少算法运行时间
- 基数缩减攻击：
   - km_deflation.cpp：论文“On the Security of the K Minimum Values (KMV) Sketch ”中3.2小节中描述攻击的复现
   - km_deflation2.cpp：我们的基数缩减攻击方案
## 二、编译
### 1. 配置要求
实验使用的环境为Ubuntu 22.04.3 LTS，g++版本为11.4.0，make版本为4.3
### 2. 编译
实验使用make命令编译运行，每个cpp文件和可执行文件的具体对应关系见Makefile文件。比如：
```c
$ make lc_bt
$ make lc_flat_s1
```
## 三、运行
### 1. Linear Counting
#### 1.1. lc_bt.cpp、lc_bt_improve.cpp、lc_flat_s1.cpp
```c
./文件名  [位图大小]
```
#### 1.2. lc_deflat.cpp
```c
./文件名  [位图大小]  [攻击集的基数缩减倍数]
```
### 2. HyperLogLog
#### 2.1. hll_infer_m.cpp
```c
./hll_infer_m [位图大小]
```
#### 2.2. hll_inflation.cpp
```c
./hll_inflation [位图大小m]  [初始集合关于位图大小m的倍数]
e.g.  ./hll_inflation 1024 10
```
#### 2.3. hll_deflation_s1_v1.cpp、hll_deflation_s1_v2.cpp、hll_deflation.cpp
```c
./[文件名] [位图大小m]  [攻击集的基数缩减倍数]
```
### 3. K Minimum Values
#### 3.1. km_infer_k.cpp
```c
./km_infer_k [样本大小K]
```
#### 3.2. km_inflation.cpp、km_inflation2.cpp、km_inflation3.cpp
```c
./[文件名] [样本大小K]   [初始集合关于K的倍数]
e.g.  ./km_inflation  1024 50，表示运行km_inflation，K值取1024，用于构造攻击集的初始集合大小为50K
```
#### 3.3. km_deflation.cpp
```c
./km_defaltion [K的取值] [参数t关于K的倍数] [攻击集的基数缩减倍数]
```
#### 3.4. km_deflation2.cpp
```c
./km_defaltion [K的取值] [攻击集的基数缩减倍数]
```
