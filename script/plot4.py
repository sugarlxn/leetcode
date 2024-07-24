import matplotlib.pyplot as plt  
  
# 数据  
configs = ['1+1+8', '1+2+4', '1+4+2', '1+8+1', '2+2+2', '2+4+1', '2+1+4']  
elapsed_time = [4698.0, 5087.4, 2617.8, 4373.6, 3330.9, 2572.3, 4318.0]  
mfu = [17.281, 15.958, 31.013, 18.563, 24.373, 31.561, 18.802]  
max_memory = [33, 25, 24, 24, 40, 40, 42]  
  
# 创建图表  
fig, axs = plt.subplots(3, 1, figsize=(10, 15))  
  
# 绘制每次迭代耗时  
axs[0].bar(configs, elapsed_time, color='b')  
axs[0].set_title('Elapsed Time per Iteration (ms)')  
axs[0].set_xlabel('dp+pp+tp Configuration')  
axs[0].set_ylabel('Time (ms)')  
  
# 绘制MFU百分比  
axs[1].bar(configs, mfu, color='g')  
axs[1].set_title('MFU (%)')  
axs[1].set_xlabel('dp+pp+tp Configuration')  
axs[1].set_ylabel('MFU (%)')  
  
# 绘制单个GPU最大内存使用量  
axs[2].bar(configs, max_memory, color='r')  
axs[2].set_title('Max Memory on Single GPU (GB)')  
axs[2].set_xlabel('dp+pp+tp Configuration')  
axs[2].set_ylabel('Memory (GB)')  
  
# 调整子图之间的间距  
plt.tight_layout()  
  
# 显示图表  
plt.show()