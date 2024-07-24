import matplotlib.pyplot as plt  
  
# 数据  
batch_sizes = [2, 4, 6, 8]  
elapsed_times = [485.7, 683.8, 905.8, 0]  
mfus = [3.0, 4.3, 4.9, 0]  
throughputs = [412, 585, 662, 0]  
gpu_memories = [36.786, 40.152, 45.560, 48.0]  
  
# 绘制2x2子图  
fig, axs = plt.subplots(2, 2, figsize=(12, 10))  
  
# 绘制Elapsed time per iteration (ms)  
axs[0, 0].plot(batch_sizes[:-1], elapsed_times[:-1], marker='o', label='Elapsed Time (ms)')  
axs[0, 0].set_title('Elapsed Time per Iteration (ms)')  
axs[0, 0].set_xlabel('Batch Size')  
axs[0, 0].set_ylabel('Elapsed Time (ms)')  
axs[0, 0].grid(True)  
axs[0, 0].legend()  
  
# 绘制MFU  
axs[0, 1].plot(batch_sizes[:-1], mfus[:-1], marker='o', label='MFU (%)')  
axs[0, 1].set_title('MFU (%)')  
axs[0, 1].set_xlabel('Batch Size')  
axs[0, 1].set_ylabel('MFU (%)')  
axs[0, 1].grid(True)  
axs[0, 1].legend()  
  
# 绘制Sample throughput (sps)  
axs[1, 0].plot(batch_sizes[:-1], throughputs[:-1], marker='o', label='Sample Throughput (sps)')  
axs[1, 0].set_title('Sample Throughput (sps)')  
axs[1, 0].set_xlabel('Batch Size')  
axs[1, 0].set_ylabel('Sample Throughput (sps)')  
axs[1, 0].grid(True)  
axs[1, 0].legend()  
  
# 绘制GPU Memory (GB)  
axs[1, 1].plot(batch_sizes, gpu_memories, marker='o', label='GPU Memory (GB)')  
axs[1, 1].set_title('GPU Memory (GB)')  
axs[1, 1].set_xlabel('Batch Size')  
axs[1, 1].set_ylabel('GPU Memory (GB)')  
#annotate the last point
axs[1, 1].annotate('Exception at GBS=8, OFM', xy=(8, 48), xytext=(5, 40),  
                arrowprops=dict(facecolor='black', shrink=0.05))
axs[1, 1].grid(True)  
axs[1, 1].legend()  
  
# 显示图表  
plt.tight_layout()  
plt.show()