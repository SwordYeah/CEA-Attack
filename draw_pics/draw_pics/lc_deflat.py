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

# Linear Counting算法基数缩减攻击相关绘图代码


def format_exponent(x, pos):
    return r'$2^{{{}}}M$'.format(int(np.log2(x)))


# 创建指数格式化对象
formatter = FuncFormatter(format_exponent)


# 不同攻击集大小下的基数缩减倍数
type = 2
if(type == 2):
    plt.clf()
    x_list = [64, 128, 256, 512, 1024]

    x_label = ['64$M$', '128$M$', '256$M$', '512$M$', '1024$M$']

    x_list_new = np.arange(5)

    deflat_time = [9, 18, 36, 73, 147]
    width = 1 / 5

    plt.plot(x_list_new, deflat_time, marker="s", color="#55b4e9", markersize=10, linewidth=3)

    # 添加标签和图例
    plt.xlabel('攻击集大小')
    # plt.xscale('log', base=2)
    plt.xticks(x_list_new, x_label)
    # plt.gca().xaxis.set_major_formatter(formatter)
    plt.ylabel('基数估计的缩减倍数')
    plt.ylim(top=160)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    # plt.legend()
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\lc_deflation_time.pdf', bbox_inches='tight')