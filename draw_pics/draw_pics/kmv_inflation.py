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

# K Minimum Values基数膨胀攻击的相关绘图代码

x_list = [50, 100, 200, 500, 1000, 5000]  # 不同初始集合大小（初始集合关于K的倍数）

x_label= ['50K', '100K', '200K', '500K', '1000K', '5000K']

width = 1/5

x_list_new = np.arange((3))


k128_origin = [0.00007319, 0.00010981, 0.00018255, 0.00037772, 0.00071527, 0.00331931] # Reviriego的方案构造攻击集的时间，K=128
k128_improve = [0.00009536, 0.00013423, 0.00020204, 0.00041222, 0.00073151, 0.00333088] # 本文的改进方案构造攻击集的时间， K=128
k128 = [k128_improve[i]/k128_origin[i] for i in range(len(k128_improve))]
k128_origin = [1000* i for i in k128_origin]
k128_improve = [1000* i for i in k128_improve]

k1024_origin = [0.00083094, 0.00119306, 0.00173390, 0.00340399, 0.00609422, 0.02729299]
k1024_improve = [0.00096113, 0.00129986, 0.00188391, 0.00350212, 0.00626331, 0.02736189]
k1024 = [k1024_improve[i]/k1024_origin[i] for i in range(len(k1024_improve))]
k1024_origin = [1000* i for i in k1024_origin]
k1024_improve = [1000* i for i in k1024_improve]

k8192_origin = [0.01458057, 0.01809909, 0.02366073, 0.03920715, 0.06164478, 0.24019607]
k8192_improve = [0.01593328, 0.01946094, 0.02513763, 0.03959050, 0.06308727, 0.24028475]
k8192 = [k8192_improve[i]/k8192_origin[i] for i in range(len(k8192_improve))]
k8192_origin = [1000* i for i in k8192_origin]
k8192_improve = [1000* i for i in k8192_improve]

k16384_origin = [0.04940637, 0.05869201, 0.07316119, 0.10703607, 0.16026610, 0.50886537]
k16384_improve = [0.05120567, 0.06144873, 0.07512230, 0.10798091, 0.16159923, 0.51427965]
k16384 = [k16384_improve[i]/k16384_origin[i] for i in range(len(k16384_improve))]
k16384_origin = [1000 * i for i in k16384_origin]
k16384_improve = [1000 * i for i in k16384_improve]

k128_our = [0.00092101, 0.00173606, 0.00344567, 0.00859033, 0.01820362]  # 本文的原始方案构造攻击集的时间， K=128
k128_our = [1000* i for i in k128_our]
k1024_our = [0.00665803, 0.01425850, 0.02958888, 0.07408090, 0.1548448]
k1024_our = [1000* i for i in k1024_our]
k8192_our = [0.06042346, 0.11897480, 0.27297026, 0.70840662, 1.48964894]
k8192_our = [1000* i for i in k8192_our]
k16384_our = [0.12176888, 0.24371278, 0.53156290, 1.47507202, 3.03607275]
k16384_our = [1000* i for i in k16384_our]




#
#
#
#
# #
# # # 绘制曲线
# # plt.plot(x_list, k128[:-1], label="K=128", marker="x")
# # plt.plot(x_list, k1024[:-1], label="K=1024", marker="x")
# # plt.plot(x_list, k8192[:-1], label="K=8192", marker="x")
# # plt.plot(x_list, k16384[:-1], label="K=16384", marker="x")
# #
# #
#


# 不同K值下，给定不同初始集合大小，Reviriego的方案和本文的原始方案构造攻击集的时间对比
K=128
if(K == 128):
    plt.clf()

    plt.bar(x_list_new - 0.5 * width, k128_origin[:3], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k128_our[:3], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:3])
    # plt.yticks(fontsize=12)
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=4)
    # plt.title('100次测试下推算出m的值')
    plt.legend()
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)

    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '.pdf', bbox_inches='tight')


K=1024
if(K == 1024):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k1024_origin[:3], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k1024_our[:3], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")

    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:3])
    # plt.yticks(fontsize=12)
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=35)
    # plt.title('100次测试下推算出m的值')
    plt.legend()
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)

    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '.pdf', bbox_inches='tight')

K=8192
if(K == 8192):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k8192_origin[:3], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k8192_our[:3], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:3])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=300)
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '.pdf', bbox_inches='tight')


K=16384
if(K == 16384):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k16384_origin[:3], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k16384_our[:3], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:3])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=600)
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '.pdf', bbox_inches='tight')


x_list_new = np.arange((5))

# 不同K值下，给定不同初始集合大小，Reviriego的方案和本文的改进方案构造攻击集的时间对比
K=128
if(K == 128):
    plt.clf()

    plt.bar(x_list_new - 0.5 * width, k128_origin[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k128_improve[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    # plt.yticks(fontsize=12)
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=0.8)
    # plt.title('100次测试下推算出m的值')
    plt.legend()
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)

    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '_1.pdf', bbox_inches='tight')


K=1024
if(K == 1024):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k1024_origin[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k1024_improve[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")

    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    # plt.yticks(fontsize=12)
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=8)
    # plt.title('100次测试下推算出m的值')
    plt.legend()
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)

    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '_1.pdf', bbox_inches='tight')

K=8192
if(K == 8192):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k8192_origin[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k8192_improve[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=80)
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '_1.pdf', bbox_inches='tight')


K=16384
if(K == 16384):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k16384_origin[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, k16384_improve[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('运行时间(ms)')
    plt.ylim(top=200)
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_time_' + str(K) + '_1.pdf', bbox_inches='tight')



x_list = [50, 100, 200, 500, 1000, 5000]



inflat_time = [i for i in x_list]

k_list = [128, 1024, 8192, 16384]

width = 1/6

x_list_new = np.arange((len(x_list)))[:-1]


k128_attack = [191, 191, 191, 191, 191, 191] # k=128情况下，Reviriego的方案构建的攻击集大小
k1024_attack = [1535, 1535, 1534, 1535, 1535, 1535]
k8192_attack = [12286, 12283, 12291, 12284, 12288, 12285]
k16384_attack = [24575, 24572, 24579, 24565, 24575, 24577]

k128_attack = [x_list[i] * k_list[0] / k128_attack[i] for i in range(len(x_list))]  # k=128情况下，Reviriego的方案构建的攻击集的基数膨胀倍数
k1024_attack = [x_list[i] * k_list[1] / k1024_attack[i] for i in range(len(x_list))]
k8192_attack = [x_list[i] * k_list[2] / k8192_attack[i] for i in range(len(x_list))]
k16384_attack = [x_list[i] * k_list[3] / k16384_attack[i] for i in range(len(x_list))]


K=128
if(K == 128):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k128_attack[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    # 本文方案构造的攻击集大小为K，假设初始集合大小为50K，攻击集造成的基数膨胀倍数就是50，因此直接取x_list内容
    plt.bar(x_list_new + 0.5 * width, inflat_time[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")

    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('基数膨胀倍数')
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_multiple_' + str(K) + '.pdf', bbox_inches='tight')

K=1024
if(K == 1024):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k1024_attack[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, inflat_time[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('基数膨胀倍数')
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_multiple_' + str(K) + '.pdf', bbox_inches='tight')

K=8192
if(K == 8192):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k8192_attack[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, inflat_time[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('基数膨胀倍数')
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_multiple_' + str(K) + '.pdf', bbox_inches='tight')


K=16384
if(K == 16384):
    plt.clf()
    plt.bar(x_list_new - 0.5 * width, k16384_attack[:-1], width, color="#4da3d4", label="Reviriego的方案", edgecolor='black', hatch="++")
    plt.bar(x_list_new + 0.5 * width, inflat_time[:-1], width, color="#eb924d", label="本文的方案", edgecolor='black', hatch="xx")


    # 添加标签和图例
    plt.xticks(x_list_new, labels=x_label[:-1])
    plt.xlabel('初始集合S的大小')
    plt.ylabel('基数膨胀倍数')
    # plt.title('100次测试下推算出m的值')
    plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
    plt.legend()
    plt.tight_layout()
    # 显示图表
    if not os.path.exists(rootdir):
        os.makedirs(rootdir)
    plt.savefig(rootdir + '\inflat_multiple_' + str(K) + '.pdf', bbox_inches='tight')



