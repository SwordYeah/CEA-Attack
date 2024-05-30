import matplotlib.pyplot as plt
import numpy as np
import os
import math
from matplotlib.ticker import FuncFormatter


plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体为宋体
# plt.rcParams['font.family'] = 'Arial'
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像时负号 '-' 显示为方块的问题
plt.rcParams["font.size"] = 16
plt.rcParams['pdf.fonttype'] = 42
plt.rcParams['ps.fonttype'] = 42

rootdir = 'D:\研三下\毕设\毕业论文\/figures\hll'

# HyperLogLog基数膨胀攻击相关绘图代码

def format_exponent(x, pos):
    return r'$2^{{{}}}M$'.format(int(np.log2(x)))


# 创建指数格式化对象
formatter = FuncFormatter(format_exponent)



# 给定不同初始集合大小的情况下得到的攻击集 A 的大小与桶的个数 M 的比值
type = 1
if(type == 1):
    plt.clf()
    x_list = [16, 32, 64, 128, 256, 512, 1024]

    x_label = ['16M', '32M', '64M', '128M', '256M', '512M', '1024M']

    x_list_new = np.arange(7)

    k_list = [1, 1, 1, 1, 1, 1, 1]
    est_list = [i * math.log(i) for i in x_list]
    width = 1 / 7

    plt.plot(x_list_new, k_list, marker="s", color="#55b4e9", markersize=10, linewidth=3)

    # 添加标签和图例
    plt.xlabel('初始集合S的大小')
    # plt.xscale('log', base=2)
    plt.xticks(x_list_new, x_label)
    # plt.gca().xaxis.set_major_formatter(formatter)
    plt.ylabel('攻击集大小和桶的个数M的比值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\hll_inflation_size.pdf', bbox_inches='tight')


# 攻击集 A 产生的基数估计与初始集合S大小的比值
type = 2
if(type == 2):
    plt.clf()
    x_list = [16, 32, 64, 128, 256, 512, 1024]


    x_label = ['16M', '32M', '64M', '128M', '256M', '512M', '1024M']

    x_list_new = np.arange(7)

    k_list = [16436, 33254, 64637, 132460, 260994, 518978, 1050848]
    for i in range(len(k_list)):
        k_list[i] = k_list[i] / 1024 / x_list[i]
    est_list = [i * math.log(i) for i in x_list]
    width = 1 / 7

    plt.plot(x_list_new, k_list, marker="s", color="#55b4e9", markersize=10, linewidth=3)

    # 添加标签和图例
    plt.xlabel('初始集合S的大小')
    # plt.xscale('log', base=2)
    plt.xticks(x_list_new, x_label)
    # plt.gca().xaxis.set_major_formatter(formatter)
    plt.ylabel('攻击集A的基数估计和集合S的比值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\hll_inflation_cardinality.pdf', bbox_inches='tight')