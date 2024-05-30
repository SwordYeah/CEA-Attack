import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter
import os

plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体为宋体
# plt.rcParams['font.family'] = 'Arial'
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像时负号 '-' 显示为方块的问题
plt.rcParams["font.size"] = 16
plt.rcParams['pdf.fonttype'] = 42
plt.rcParams['ps.fonttype'] = 42

rootdir = 'D:\研三下\毕设\毕业论文\/figures\kmv'

# K Minimum Values算法推测K值的相关绘图代码


def format_exponent(x, pos):
    return r'$2^{{{}}}$'.format(int(np.log2(x)))


# 创建指数格式化对象
formatter = FuncFormatter(format_exponent)


# 不同 K 值下 计算出的近似值 K1 的相对误差
x_list = [64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]

# x = np.arange(len(x_list))

err_list = [0.55625000, 0.32734375, 0.14335938, 0.06269531, 0.03310547, 0.01791992, 0.00876465, 0.00445557, 0.00212402]

plt.plot(x_list, err_list, marker="s", color="#55b4e9", markersize=10, linewidth=3)




# 添加标签和图例
plt.xlabel('K')
plt.xscale('log', base=2)
plt.xticks(x_list)
plt.gca().xaxis.set_major_formatter(formatter)
plt.ylabel('$K_1$的相对误差(%)')
plt.ylim(top=0.6)
plt.grid(axis='y', linestyle='--', color='gray', alpha=0.5)
plt.tight_layout()
# 显示图表
# plt.show()
if not os.path.exists(rootdir):
    os.makedirs(rootdir)
plt.savefig(rootdir + '\infer_k.pdf', bbox_inches='tight')