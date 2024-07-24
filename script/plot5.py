import matplotlib.pyplot as plt  
import numpy as np  
  
# 数据  
global_batch_sizes = [2, 4, 6, 7, 8]  # 忽略了导致异常的全局批处理大小8的迭代时间和MFU  
elapsed_times = [2617.8, 4696.2, 6654.2, 7723.5, 0]  # 但为了完整性，我还是包含了它  
mfus = [31.013, 34.575, 36.602, 36.790, 0]  
max_memories = [24, 31, 41, 47, 48]  
  
# 排除导致异常的点（可选，但在这个例子中我们保留它们以显示问题）  
# 如果选择排除，可以这样做：  
# elapsed_times = [t for t, gbs in zip(elapsed_times, global_batch_sizes) if gbs != 8]  
# mfus = [m for m, gbs in zip(mfus, global_batch_sizes) if gbs != 8]  
# global_batch_sizes = [gbs for gbs in global_batch_sizes if gbs != 8]  
  
# 创建图表  
fig, axs = plt.subplots(3, 1, figsize=(10, 15))  
  
# 绘制每次迭代耗时  
axs[0].plot(global_batch_sizes, elapsed_times, marker='o')  
axs[0].set_title('Elapsed Time per Iteration (ms)')  
axs[0].set_xlabel('Global Batch Size')  
axs[0].set_ylabel('Time (ms)')  
axs[0].annotate('Exception at GBS=8', xy=(8, 0), xytext=(6, 3000),  
                arrowprops=dict(facecolor='black', shrink=0.05))  
  
# 绘制MFU百分比  
axs[1].plot(global_batch_sizes, mfus, marker='o')  
axs[1].set_title('MFU (%)')  
axs[1].set_xlabel('Global Batch Size')  
axs[1].set_ylabel('MFU (%)')  
axs[1].annotate('Exception at GBS=8', xy=(8, 0), xytext=(6, 25),  
                arrowprops=dict(facecolor='black', shrink=0.05))  
  
# 绘制单个GPU最大内存使用量  
axs[2].plot(global_batch_sizes, max_memories, marker='o')  
axs[2].set_title('Max Memory on Single GPU (GB)')  
axs[2].set_xlabel('Global Batch Size')  
axs[2].set_ylabel('Memory (GB)')  
axs[2].annotate('Exception at GBS=8, OFM', xy=(8, 48), xytext=(6, 25),  
                arrowprops=dict(facecolor='black', shrink=0.05))  
  
# 调整子图之间的间距  
plt.tight_layout()  
  
# 显示图表  
plt.show()