import matplotlib.pyplot as plt  
import numpy as np
  
# 数据  
data = [  
    ('PCIe 4', '1+1+2p', 670.4, 35.2, 9547),  
    ('PCIe 4', '1+2+1p', 755.1, 31.2, 8476),  
    ('PCIe 4', '2+1+1p', 414.2, 57.0, 15451),  
    ('NVLink', '1+1+2n', 480.8, 49.0, 13311),  
    ('NVLink', '1+2+1n', 737.0, 32.0, 8683),  
    ('NVLink', '2+1+1n', 408.0, 57.8, 15686),  
]  
  
# 分离数据为NVLink和PCIe两组  
nvlink_data = [(dp_pp_tp, elapsed_time, mfu, throughput) for link_type, dp_pp_tp, elapsed_time, mfu, throughput in data if link_type == 'NVLink']  
pcie_data = [(dp_pp_tp, elapsed_time, mfu, throughput) for link_type, dp_pp_tp, elapsed_time, mfu, throughput in data if link_type == 'PCIe 4']  
  
# 提取NVLink和PCIe的dp+pp+tp和对应的值  
nvlink_dp_pp_tp, nvlink_elapsed_time, nvlink_mfu, nvlink_throughput = zip(*nvlink_data)  
pcie_dp_pp_tp, pcie_elapsed_time, pcie_mfu, pcie_throughput = zip(*pcie_data)  
  
# 创建图表  
fig, axs = plt.subplots(3, 1, figsize=(10, 15))  
  
# 绘制每次迭代耗时  
axs[0].bar(nvlink_dp_pp_tp, nvlink_elapsed_time, label='NVLink', color='b')  
axs[0].bar(pcie_dp_pp_tp, pcie_elapsed_time, label='PCIe 4', color='r')  
axs[0].set_title('Elapsed Time per Iteration (ms)')  
axs[0].set_xlabel('dp+pp+tp')  
axs[0].set_ylabel('Time (ms)')  
axs[0].legend()  
  

# 绘制MFU百分比  
axs[1].bar(nvlink_dp_pp_tp, nvlink_mfu, label='NVLink', color='b')  
axs[1].bar(pcie_dp_pp_tp, pcie_mfu, label='PCIe 4', color='r')  
axs[1].set_title('MFU (%)')  
axs[1].set_xlabel('dp+pp+tp')  
axs[1].set_ylabel('MFU (%)')  
axs[1].legend()  
  

# 绘制样本吞吐量  
axs[2].bar(nvlink_dp_pp_tp, nvlink_throughput, label='NVLink', color='b')  
axs[2].bar(pcie_dp_pp_tp, pcie_throughput, label='PCIe 4', color='r')  
axs[2].set_title('Sample Throughput (sps)')  
axs[2].set_xlabel('dp+pp+tp')  
axs[2].set_ylabel('Sample Throughput (sps)')  
axs[2].legend()  
  

# plt.tight_layout()
plt.show()