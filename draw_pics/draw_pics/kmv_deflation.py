import math

import matplotlib.pyplot as plt
import numpy as np
import os

plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体为宋体
# plt.rcParams['font.family'] = 'Arial'
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像时负号 '-' 显示为方块的问题
plt.rcParams["font.size"] = 22
plt.rcParams['pdf.fonttype'] = 42
plt.rcParams['ps.fonttype'] = 42

rootdir = 'D:\研三下\毕设\毕业论文\/figures\kmv'

# K Minimum Values基数缩减攻击的相关绘图代码


# 不同 K 值与基数缩减倍数下构建攻击集的时间对比
x_list = [10, 100, 1000]  # 不同的基数缩减倍数

width = 0.2

x = np.arange(len(x_list))


# # 标签
# plt.bar(x - 1.5* width, x, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
# plt.bar(x - 0.5 * width, x, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
# plt.bar(x + 0.5 * width, x, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
# plt.bar(x + 1.5 * width, x, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")
# plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.17), ncol=4)
# plt.tight_layout()
#
# # 显示图表
# plt.show()

K = 1024
if (K == 1024):
    t_k_origin = [0.00812227, 0.04510557, 0.91894655]  # Reviriego的方案，t=K构造攻击集的运行时间
    t_2k_origin = [0.00595376,0.05688946, 0.57861673]  # Reviriego的方案，t=2K构造攻击集的运行时间
    t_8k_origin = [0.00512055, 0.04902928, 0.52107721] # Reviriego的方案，t=8K构造攻击集的运行时间
    deflat_improve = [0.00346102, 0.02928815, 0.29423579] # 本文方案构建攻击集的运行时间

    # 创建两个绘图坐标轴；调整两个轴之间的距离，即轴断点距离
    plt.clf()
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)
    fig.subplots_adjust(hspace=0.2)  # adjust space between axes

    # 绘制曲线
    ax1.bar(x - 1.5* width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax1.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax1.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax1.bar(x + 1.5 * width, deflat_improve, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")

    ax2.bar(x - 1.5 * width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax2.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax2.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax2.bar(x + 1.5 * width, deflat_improve, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")


    # 添加数据标注
    # for i in range(len(x_list)):
    #     ax2.text(x[i] - width, t_k_origin[i], str(t_k_origin[i]), ha='center', va='bottom')
    #     ax2.text(x[i], t_2k_origin[i], str(t_2k_origin[i]), ha='center', va='bottom')
    #     ax2.text(x[i], t_8k_origin[i], str(t_8k_origin[i]), ha='center', va='bottom')
    #     # ax1.text(x[i] + width, real_list_our[i], str(real_list_our[i]), ha='center', va='bottom')
    #
    #     # ax2.text(x[i] - width, real_list[i], str(real_list[i]), ha='center', va='bottom')
    #     # ax2.text(x[i], real_list2[i], str(real_list2[i]), ha='center', va='bottom')
    #     ax1.text(x[i] + width, deflat_improve[i], str(deflat_improve[i]), ha='center', va='bottom')

    # 调整两个y轴的显示范围
    ax1.set_ylim(0.25, 1)  # outliers only
    ax2.set_ylim(0, 0.06)  # most of the data

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

    # 添加标签和图例
    plt.xlabel('基数缩减倍数')
    # plt.ylabel('运行时间(s)')
    ax1.set_ylabel('运行时间(s)', labelpad=30)  # 设置标签与轴的距离
    ax1.yaxis.set_label_coords(-0.3, -0.15)  # 调整位置

    # fig.text(0.02, 0.5, '运行时间(s)', va='center', rotation='vertical')
    plt.xticks(x, labels=x_list)
    ax1.set_yticks([0.25, 0.5, 0.75, 1.00])
    ax2.set_yticks([0, 0.03, 0.06])
    # plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.17), ncol=4)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    # plt.ylim(1.45, 1.55)
    plt.tight_layout()
    fig.subplots_adjust(hspace=0.3)  # adjust space between axes
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\deflat_' + str(K) + '.pdf', bbox_inches='tight')

K = 128
if(K == 128):

    t_k_origin = [0.00060434, 0.00629556, 0.05764210]
    t_2k_origin = [0.00045758, 0.00429210, 0.04192337]
    t_8k_origin = [0.00041409, 0.00400795, 0.03815356]
    deflat_improve = [0.00041247, 0.00371082, 0.03622245]

    # 创建两个绘图坐标轴；调整两个轴之间的距离，即轴断点距离
    plt.clf()
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)
    fig.subplots_adjust(hspace=0.2)  # adjust space between axes

    # 绘制曲线
    ax1.bar(x - 1.5 * width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax1.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax1.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax1.bar(x + 1.5 * width, deflat_improve, width, label="我们的方案", color="#eb924d", edgecolor='black', hatch="xx")

    ax2.bar(x - 1.5 * width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax2.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax2.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax2.bar(x + 1.5 * width, deflat_improve, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")


    # 调整两个y轴的显示范围
    ax1.set_ylim(0.03, 0.06)  # outliers only
    ax2.set_ylim(0, 0.01)  # most of the data

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

    # 添加标签和图例
    plt.xlabel('基数缩减倍数')
    # plt.ylabel('运行时间(s)')
    ax1.set_ylabel('运行时间(s)', labelpad=30) # 设置标签与轴的距离
    ax1.yaxis.set_label_coords(-0.3, -0.15)  # 调整位置

    # fig.text(-0.01, 0.5, '运行时间(s)', va='center', rotation='vertical')
    plt.xticks(x, labels=x_list)
    ax1.set_yticks([0.03, 0.045, 0.06])
    ax2.set_yticks([0, 0.005, 0.01])
    # plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.17), ncol=4)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    # plt.ylim(1.45, 1.55)
    plt.tight_layout()
    fig.subplots_adjust(hspace=0.3)  # adjust space between axes
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\deflat_' + str(K) + '.pdf', bbox_inches='tight')

K= 8192
if(K == 8192):
    t_k_origin = [0.17153770, 1.71720599, 17.71743038]
    t_2k_origin = [0.12462540, 1.24845414, 12.54530705]
    t_8k_origin = [0.10024819, 1.01214975, 10.30676551]
    deflat_improve = [0.03403799, 0.23616149, 2.25975549]

    # 创建两个绘图坐标轴；调整两个轴之间的距离，即轴断点距离
    plt.clf()
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)
    fig.subplots_adjust(hspace=0.2)  # adjust space between axes

    # 绘制曲线
    ax1.bar(x - 1.5 * width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax1.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax1.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax1.bar(x + 1.5 * width, deflat_improve, width, label="我们的方案", color="#eb924d", edgecolor='black', hatch="xx")

    ax2.bar(x - 1.5 * width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax2.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax2.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax2.bar(x + 1.5 * width, deflat_improve, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")

    # 调整两个y轴的显示范围
    ax1.set_ylim(10, 20)  # outliers only
    ax2.set_ylim(0, 3)  # most of the data

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

    # 添加标签和图例
    plt.xlabel('基数缩减倍数')
    # plt.ylabel('运行时间(s)')
    ax1.set_ylabel('运行时间(s)', labelpad=30)  # 设置标签与轴的距离
    ax1.yaxis.set_label_coords(-0.2, -0.15)  # 调整位置

    # fig.text(-0.01, 0.5, '运行时间(s)', va='center', rotation='vertical')
    plt.xticks(x, labels=x_list)
    ax1.set_yticks([10.0, 15.0, 20.0])
    ax2.set_yticks([0, 1.5, 3])
    # plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.17), ncol=4)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    # plt.ylim(1.45, 1.55)
    plt.tight_layout()
    fig.subplots_adjust(hspace=0.3)  # adjust space between axes
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\deflat_' + str(K) + '.pdf', bbox_inches='tight')



K= 16384
if(K == 16384):
    t_k_origin = [0.62883225, 6.33659645, 63.31628962]
    t_2k_origin = [0.44304550, 4.42905827, 45.17918058]
    t_8k_origin = [0.38331166, 3.68926444, 40.75693326]
    deflat_improve = [0.09276136, 0.52163812, 4.96119959]

    # 创建两个绘图坐标轴；调整两个轴之间的距离，即轴断点距离
    plt.clf()
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)
    fig.subplots_adjust(hspace=0.2)  # adjust space between axes

    # 绘制曲线
    ax1.bar(x - 1.5 * width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax1.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax1.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax1.bar(x + 1.5 * width, deflat_improve, width, label="我们的方案", color="#eb924d", edgecolor='black', hatch="xx")

    ax2.bar(x - 1.5 * width, t_k_origin, width, label="Reviriego的方案，t=K", color="#4da3d4", edgecolor='black', hatch="--")
    ax2.bar(x - 0.5 * width, t_2k_origin, width, label="Reviriego的方案，t=2K", color="#9470b7", edgecolor='black', hatch="//")
    ax2.bar(x + 0.5 * width, t_8k_origin, width, label="Reviriego的方案，t=8K", color="#4dbb9d", edgecolor='black', hatch="++")
    ax2.bar(x + 1.5 * width, deflat_improve, width, label="本文的方案", color="#eb924d", edgecolor='black', hatch="xx")

    # 调整两个y轴的显示范围
    ax1.set_ylim(35, 65)  # outliers only
    ax2.set_ylim(0, 10)  # most of the data

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

    # 添加标签和图例
    plt.xlabel('基数缩减倍数')
    # plt.ylabel('运行时间(s)')
    ax1.set_ylabel('运行时间(s)', labelpad=30)  # 设置标签与轴的距离
    ax1.yaxis.set_label_coords(-0.2, -0.15)  # 调整位置

    # fig.text(-0.01, 0.5, '运行时间(s)', va='center', rotation='vertical')
    plt.xticks(x, labels=x_list)
    ax1.set_yticks([35, 50, 65])
    ax2.set_yticks([0, 5, 10])
    # plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.17), ncol=4)
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    # plt.ylim(1.45, 1.55)
    plt.tight_layout()
    fig.subplots_adjust(hspace=0.3)  # adjust space between axes
    # 显示图表
    # plt.show()
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\deflat_' + str(K) + '.pdf', bbox_inches='tight')
