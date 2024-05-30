import matplotlib.pyplot as plt
import numpy as np
import os
from matplotlib.ticker import FuncFormatter


plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体为宋体
# plt.rcParams['font.family'] = 'Arial'
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像时负号 '-' 显示为方块的问题
plt.rcParams["font.size"] = 16
plt.rcParams['pdf.fonttype'] = 42
plt.rcParams['ps.fonttype'] = 42

rootdir = 'D:\研三下\毕设\毕业论文\/figures\hll'

# 推测HyperLogLog使用桶的取值相关绘图代码


def format_exponent(x, pos):
    return r'$2^{{{}}}$'.format(int(np.log2(x)))


# 创建指数格式化对象
formatter = FuncFormatter(format_exponent)


# 不同 M 取值下算法推算出的近似值 M1 的相对误差
x_list = [128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536]

err_list = [36.7812, 14.8125, 0.175781, 0.0488281, 0.0341797, 0.0244141, 0.00732422, 0.00488281, 0.00152588, 0.000610352]

plt.plot(x_list, err_list, marker="s", color="#55b4e9", markersize=10, linewidth=3)




# 添加标签和图例
plt.xlabel('M')
plt.xscale('log', base=2)
plt.xticks(x_list)
plt.gca().xaxis.set_major_formatter(formatter)
plt.ylabel('$M_1$的相对误差(%)')
plt.ylim(top=40)
plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
plt.tight_layout()
# 显示图表
# plt.show()
if not os.path.exists(rootdir):
    os.makedirs(rootdir)
plt.savefig(rootdir + '\infer_m.pdf', bbox_inches='tight')