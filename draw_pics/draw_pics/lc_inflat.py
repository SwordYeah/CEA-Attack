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

rootdir = 'D:\研三下\毕设\毕业论文\/figures\lc'

# Linear Counting算法基数膨胀攻击相关绘图代码



def format_exponent(x, pos):
    return r'$2^{{{}}}$'.format(int(np.log2(x)))


# 创建指数格式化对象
formatter = FuncFormatter(format_exponent)


# 攻击集的实际基数膨胀倍数和理论值的对比
type = 1
if(type == 1):
    x_list = [256, 512, 1024, 2048,  4096]

    x_list_new = np.arange(5)

    est_list = [1419, 3194, 7097, 15615, 34069]  # 基数估计值

    for i in range(len(est_list)):
        est_list[i] /= x_list[i]  # 实际基数估计膨胀倍数

    # est_theory = [1420, 7098, 34070, 158991]

    est_theory = [math.log(256), math.log(512), math.log(1024), math.log(2048), math.log(4096)]  # 理论基数估计膨胀倍数
    width = 1 / 5

    # plt.bar(x_list_new - 0.5 * width, est_theory, width, color="#4da3d4", label="理论上界")
    # plt.bar(x_list_new + 0.5 * width, est_list, width, color="#eb924d", label="实际攻击效果")

    plt.plot(x_list_new, est_list, marker="d", markerfacecolor='none',color="#eb924d", markersize=16, markeredgewidth=2, linewidth=3, label="实际效果")
    plt.plot(x_list_new, est_theory, marker="+", color="#4da3d4", markersize=13, markeredgewidth=2.5, linewidth=3,
             label="理论上界")

    # 添加标签和图例
    plt.xlabel('桶的个数$M$')
    # plt.xscale('log', base=2)
    plt.xticks(x_list_new, labels=x_list)
    plt.ylabel('基数估计的膨胀倍数')
    plt.ylim(top=8.5)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\lc_inflation_time.pdf', bbox_inches='tight')


# 攻击集大小和基数估计值的大小比较
type = 2
if(type == 2):
    plt.clf()
    x_list = [256, 512, 1024, 2048, 4096]

    x_list_new = np.arange(5)

    est_list = [i * math.log(i) for i in x_list]

    # for i in range(len(est_list)):
    #     est_list[i] /= x_list[i]

    # est_theory = [1420, 7098, 34070, 158991]

    est_theory = [math.log(256), math.log(1024), math.log(4096), math.log(16384)]
    width = 1 / 5

    plt.bar(x_list_new - 0.5 * width, x_list, width, color="#4da3d4", label="攻击集", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, est_list, width, color="#eb924d", label="基数估计", edgecolor='black', hatch="xx")

    # 添加标签和图例
    plt.xlabel('桶的个数$M$')
    # plt.xscale('log', base=2)
    plt.xticks(x_list_new, labels=x_list)
    plt.ylabel('大小')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\lc_inflation_size.pdf', bbox_inches='tight')