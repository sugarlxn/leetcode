#!/usr/bin/env python3
import matplotlib.pyplot as plt  
  
# 数据  
data = [  
    ('118', 1737.3, 3.4, 3684),  
    ('124', 1952.7, 3.0, 3278),  
    ('142', 914.6, 6.4, 6998),  
    ('181', 1169.7, 5.0, 5471),  
    ('214', 1081.1, 5.5, 5920),  
    ('222', 506.9, 11.6, 12626),  
    ('241', 675.8, 8.7, 9470),  
    ('412', 319.8, 18.4, 20013),  
    ('421', 421.4, 14.0, 15187),  
    ('811', 296.1, 19.9, 21614)  
]  
  
# 提取数据  
dp_pp_tp = [d[0] for d in data]  
elapsed_times = [d[1] for d in data]  
mfus = [d[2] for d in data]  
throughputs = [d[3] for d in data]  
  
# 绘制柱状图  
fig, axs = plt.subplots(3, 1, figsize=(10, 15))  
  
# 绘制Elapsed time per iteration (ms)  
axs[0].bar(dp_pp_tp, elapsed_times, color='skyblue')  
axs[0].set_title('Elapsed Time per Iteration (ms)')  
axs[0].set_xlabel('dp+pp+tp')  
axs[0].set_ylabel('Time (ms)')  
axs[0].set_xticklabels(dp_pp_tp, rotation=45, ha="right")  
  
# 绘制MFU  
axs[1].bar(dp_pp_tp, mfus, color='green')  
axs[1].set_title('MFU (%)')  
axs[1].set_xlabel('dp+pp+tp')  
axs[1].set_ylabel('MFU (%)')  
axs[1].set_xticklabels(dp_pp_tp, rotation=45, ha="right")  
  
# 绘制Sample throughput (sps)  
axs[2].bar(dp_pp_tp, throughputs, color='orange')  
axs[2].set_title('Sample Throughput (sps)')  
axs[2].set_xlabel('dp+pp+tp')  
axs[2].set_ylabel('Throughput (sps)')  
axs[2].set_xticklabels(dp_pp_tp, rotation=45, ha="right")  
  
# 调整子图之间的间距  
plt.tight_layout()  
  
# 显示图形  
plt.show()