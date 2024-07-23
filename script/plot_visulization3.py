#!/usr/bin/env python3
import matplotlib.pyplot as plt  
  
# 数据  
batch_sizes = [2, 4, 8, 16, 32, 64]  
elapsed_times = [169.9, 188.5, 193.0, 250.9, 395.3, 693.6]  
mfus = [8.7, 15.6, 30.5, 47.0, 59.7, 68.0]  
throughputs = [1177, 2122, 4145, 6377, 8095, 9227]  
gpu_memories = [4.052, 5.096, 8.004, 13.638, 25.006, 47.762]  
  
# 创建图形和子图  
fig, axs = plt.subplots(2, 2, figsize=(12, 8))  
  
# 绘制每次迭代的耗时  
axs[0, 0].plot(batch_sizes, elapsed_times, marker='o')  
axs[0, 0].set_title('Elapsed Time per Iteration (ms)')  
axs[0, 0].set_xlabel('Batch Size')  
axs[0, 0].set_ylabel('Time (ms)')  
  
# 绘制MFU  
axs[0, 1].plot(batch_sizes, mfus, marker='o')  
axs[0, 1].set_title('MFU (%)')  
axs[0, 1].set_xlabel('Batch Size')  
axs[0, 1].set_ylabel('MFU (%)')  
  
# 绘制样本吞吐量  
axs[1, 0].plot(batch_sizes, throughputs, marker='o')  
axs[1, 0].set_title('Sample Throughput (sps)')  
axs[1, 0].set_xlabel('Batch Size')  
axs[1, 0].set_ylabel('Throughput (sps)')  
  
# 绘制GPU内存使用量  
axs[1, 1].plot(batch_sizes, gpu_memories, marker='o')  
axs[1, 1].set_title('GPU Memory (GB)')  
axs[1, 1].set_xlabel('Batch Size')  
axs[1, 1].set_ylabel('Memory (GB)')  
  
# 调整子图布局  
plt.tight_layout()  
  
# 显示图形  
plt.show()