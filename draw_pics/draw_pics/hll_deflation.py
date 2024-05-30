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



# 给定不同初始集合大小的情况下得到的攻击集 A 的大小与初始集合 S 大小的比值
type = 1
if(type == 1):
    plt.clf()
    x_list = [16, 32, 64, 128, 256, 512, 1024]

    x_label = ['16M', '32M', '64M', '128M', '256M', '512M', '1024M']

    x_list_new = np.arange(7)

    attack_list = [12260, 24486, 49002, 98034, 195873, 391544, 784033]
    for i in range(len(attack_list)):
        attack_list[i] = attack_list[i] / 1024 / x_list[i]

    est_list = [i * math.log(i) for i in x_list]
    width = 1 / 7

    plt.plot(x_list_new, attack_list, marker="s", color="#55b4e9", markersize=10, linewidth=3)

    # 添加标签和图例
    plt.xlabel('初始集合S的大小')
    # plt.xscale('log', base=2)
    plt.xticks(x_list_new, x_label)
    # plt.gca().xaxis.set_major_formatter(formatter)
    plt.ylabel('攻击集大小和集合S的比值')
    plt.ylim(top=0.7485)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\hll_deflation_fraction.pdf', bbox_inches='tight')


# 给定不同初始集合大小的情况下得到的攻击集 A的大小与基数估计的比值
type = 2
if(type == 2):
    plt.clf()
    x_list = [16, 32, 64, 128, 256, 512, 1024]

    x_label = ['16M', '32M', '64M', '128M', '256M', '512M', '1024M']

    x_list_new = np.arange(7)

    attack_list = [12260, 24486, 49002, 98034, 195873, 391544, 784033]


    est_list = [2866, 2916, 2919, 2918, 2911, 2912, 2922]
    for i in range(len(attack_list)):
        attack_list[i] = attack_list[i] / est_list[i]

    est_list = [i * math.log(i) for i in x_list]
    width = 1 / 7

    plt.plot(x_list_new, attack_list, marker="s", color="#55b4e9", markersize=10, linewidth=3)

    # 添加标签和图例
    plt.xlabel('初始集合S的大小')
    # plt.xscale('log', base=2)
    plt.xticks(x_list_new, x_label)
    # plt.gca().xaxis.set_major_formatter(formatter)
    plt.ylabel('基数缩减倍数')
    plt.ylim(top=300)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\hll_deflation_time.pdf', bbox_inches='tight')


# 不同算法构建具有相同基数缩减数的攻击集花费的时间对比
type = 3
if(type == 3):
    plt.clf()
    x_list = [64, 256, 1024]

    time_list = [0.295663, 1.19851, 4.81459]

    time_list2 = [1.33435, 7.01848, 35.7033]

    time_list_our = [3.96061, 12.9006, 45.812]

    width = 0.3

    x = np.arange(3)

    plt.clf()
    plt.bar(x - width, time_list, width, label="Paterson的方案一", color="#4da3d4", edgecolor='black', hatch="//")
    plt.bar(x, time_list2, width, label="Paterson的方案二", color="#4dbb9d", edgecolor='black', hatch="++")
    plt.bar(x + width, time_list_our, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")

    # 添加标签和图例
    plt.xlabel('攻击集的基数缩减倍数')
    plt.xticks(x, x_list)
    # plt.xscale('log', base=2)
    plt.ylabel('构造攻击集的时间(s)')
    plt.ylim(top=50)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    plt.legend()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\deflation_time_compare.pdf', bbox_inches='tight')


# 不同算法构建具有相同理论基数缩减数的攻击集在非空 sketch 中造成的实际基数缩减倍数对比
type = 4
if(type == 4):
    plt.clf()
    x_list = [64, 256, 1024]

    est_list = [5140, 5699, 5251]

    est_list2 = [6132, 7063, 6500]

    est_list_our = [525, 615, 552]

    real_list = [45416, 181665, 726663]
    for i in range(len(real_list)):
        real_list[i] = int(real_list[i] / est_list[i])

    real_list2 = [45546, 182131, 726645]
    for i in range(len(real_list2)):
        real_list2[i] = int(real_list2[i] / est_list2[i])

    real_list_our = [188743, 754974, 3019898]
    for i in range(len(real_list_our)):
        real_list_our[i] = int(real_list_our[i] / est_list_our[i])

    x = np.arange(3)

    width = 1 / 4

    # 创建两个绘图坐标轴；调整两个轴之间的距离，即轴断点距离
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)
    fig.subplots_adjust(hspace=0.05)  # adjust space between axes

    # 将用相同的绘图数据，在两个轴上绘制折线
    ax1.bar(x - width, real_list, width, label="Paterson的方案一", color="#4da3d4", edgecolor='black', hatch="//")
    ax1.bar(x, real_list2, width, label="Paterson的方案二", color="#4dbb9d", edgecolor='black', hatch="++")
    ax1.bar(x + width, real_list_our, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")

    ax2.bar(x - width, real_list, width, label="Paterson的方案一", color="#4da3d4", edgecolor='black', hatch="//")
    ax2.bar(x, real_list2, width, label="Paterson的方案二", color="#4dbb9d", edgecolor='black', hatch="++")
    ax2.bar(x + width, real_list_our, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")

    # 添加数据标注
    for i in range(len(x_list)):
        ax2.text(x[i] - width, real_list[i], str(real_list[i]), ha='center', va='bottom')
        ax2.text(x[i], real_list2[i], str(real_list2[i]), ha='center', va='bottom')
        # ax1.text(x[i] + width, real_list_our[i], str(real_list_our[i]), ha='center', va='bottom')

        # ax2.text(x[i] - width, real_list[i], str(real_list[i]), ha='center', va='bottom')
        # ax2.text(x[i], real_list2[i], str(real_list2[i]), ha='center', va='bottom')
        ax1.text(x[i] + width, real_list_our[i], str(real_list_our[i]), ha='center', va='bottom')

    # 调整两个y轴的显示范围
    ax1.set_ylim(300, 6300)  # outliers only
    ax2.set_ylim(0, 150)  # most of the data

    # 隐藏两个坐标轴系列之间的横线
    ax1.spines.bottom.set_visible(False)
    ax2.spines.top.set_visible(False)
    ax1.xaxis.tick_top()

    # 隐藏y轴刻度
    ax1.tick_params(axis='x', length=0)
    # ax2.xaxis.tick_bottom()

    # 添加网格线
    ax1.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    ax2.grid(axis='y', linestyle='--', color='gray', alpha=0.5)

    # 创建轴断刻度线，d用于调节其偏转角度
    d = 0.5  # proportion of vertical to horizontal extent of the slanted line
    kwargs = dict(marker=[(-1, -d), (1, d)], markersize=12,
                  linestyle="none", color='k', mec='k', mew=1, clip_on=False)
    ax1.plot([0, 1], [0, 0], transform=ax1.transAxes, **kwargs)
    ax2.plot([0, 1], [1, 1], transform=ax2.transAxes, **kwargs)

    ax1.set_yticks([300, 2300, 4300, 6300])

    plt.xlabel('攻击集的理论基数缩减倍数')
    plt.xticks(x, x_list)
    # plt.xscale('log', base=2)
    # 共享y轴标题
    ax1.set_ylabel('实际基数缩减倍数', labelpad=10)  # 设置标签与轴的距离
    ax1.yaxis.set_label_coords(-0.12, -0.18)  # 调整位置
    # fig.text(0.02, 0.5, '实际基数缩减倍数', va='center', rotation='vertical')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.tight_layout()
    ax1.legend()
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\deflation_size_compare.pdf', bbox_inches='tight')