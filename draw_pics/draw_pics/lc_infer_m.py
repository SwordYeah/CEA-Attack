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

# Linear Counting算法推测位图大小相关绘图代码

x = np.arange(3)

width = 0.15

label_list = ['0.5M', 'M', '2M']

# 不同M取值下F关于x的取值
list_256 = [78.9, 63.3, 43.3]

list_2048 = [78.8, 63.2, 43.2]

list_16384 = [78.6, 63.3, 43.2]



def format_exponent(x, pos):
    return r'$2^{{{}}}$'.format(int(np.log2(x)))


# 创建指数格式化对象
formatter = FuncFormatter(format_exponent)

type = 1
if(type == 1):
    plt.clf()
    plt.bar(x - 1.* width, list_256, width, label="M=256", color="#4dbb9d", edgecolor='black', hatch="//")
    plt.bar(x , list_2048, width, label="M=2048", color="#9470b7", edgecolor='black', hatch="++")
    plt.bar(x + 1 * width, list_16384, width, label="M=16384", color="#4da3d4", edgecolor='black', hatch="xx")



    # 添加标签和图例
    plt.xticks(x, labels=label_list)
    plt.xlabel('$x$')
    plt.ylabel('$F$')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\/real_f.pdf', bbox_inches='tight')



# 绘制非空桶和扔出球的比值理论曲线
type = 2
if(type == 2):
    plt.clf()
    # 定义 x 的范围
    x = np.linspace(0, 5, 100)

    # 计算对应的 y 值
    y = (1 - pow(math.e, -x[1:]))/x[1:]

    # 绘制曲线
    plt.plot(x[1:], y, color="#55b4e9", markersize=10, linewidth=3)

    # 添加标签和标题
    plt.xlabel('$x$')
    plt.ylabel('$F$')
    # plt.title('y = x^2')

    # 显示图形
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\/theory_f.pdf', bbox_inches='tight')

# 不同 M 取值下两种算法推算出近似值 M1 的相对误差
type = 3
if(type == 3):
    plt.clf()
    x_list = [128, 256, 512, 1024, 2048, 4096]

    err_list = [31.25, 6.94, 3.95, 3.18, 2.02, 1.39]

    err_list_improve = [6.5, 0, 0, 0, 0, 0]

    plt.plot(x_list, err_list, marker="s", color="#55b4e9", label="推测桶的个数的算法3-1", markersize=10, markeredgewidth=2, linewidth=3)
    plt.plot(x_list, err_list_improve, marker="D", color="#eb924d", label="推测桶的个数的改进算法3-2", markersize=10, linewidth=3)




    # 添加标签和图例

    plt.xlabel('$M$')
    plt.xscale('log', base=2)
    # 设置刻度标签
    plt.xticks(x_list)
    plt.gca().xaxis.set_major_formatter(formatter)
    plt.ylabel('$M_1$的相对误差(%)')
    plt.ylim(top=35)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    plt.legend()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\/test_m.pdf', bbox_inches='tight')


# type = 4
# if(type == 4):
#     plt.clf()
#     x_list = [128, 256, 512, 1024, 2048, 4096]
#
#     err_list = [6.5, 0, 0, 0, 0, 0]
#
#     plt.plot(x_list, err_list, marker="s", color="#55b4e9", markersize=10, linewidth=3)
#
#     # 添加标签和图例
#     plt.xlabel('M')
#     plt.xscale('log', base=2)
#     plt.xticks(x_list)
#     plt.gca().xaxis.set_major_formatter(formatter)
#     plt.ylabel('$M_1$的相对误差(%)')
#     plt.ylim(top=7)
#     plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
#     plt.tight_layout()
#     # 显示图表
#     # plt.show()
#     if not os.path.exists('D:\研三下\毕设\毕业论文模板\/figures\lc'):
#         os.makedirs('D:\研三下\毕设\毕业论文模板\/figures\lc')
#     plt.savefig('D:\研三下\毕设\毕业论文模板\/figures\lc\/test_m_improve1.pdf', bbox_inches='tight')
