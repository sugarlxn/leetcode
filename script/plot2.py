import matplotlib.pyplot as plt  
  
# 定义数据  
data = {  
    'PCIe 4': [  
        {'dp+pp+tp': '1+1+2', 'time': 670.4, 'MFU': 35.2, 'sps': 9547},  
        {'dp+pp+tp': '1+2+1', 'time': 755.1, 'MFU': 31.2, 'sps': 8476},  
        {'dp+pp+tp': '2+1+1', 'time': 414.2, 'MFU': 57.0, 'sps': 15451}  
    ],  
    'NVLink': [  
        {'dp+pp+tp': '1+1+2', 'time': 480.8, 'MFU': 49.0, 'sps': 13311},  
        {'dp+pp+tp': '1+2+1', 'time': 737.0, 'MFU': 32.0, 'sps': 8683},  
        {'dp+pp+tp': '2+1+1', 'time': 408.0, 'MFU': 57.8, 'sps': 15686}  
    ]  
}  
  
# 绘制每个度量指标的图表  
def plot_all_metrics():  
    fig, axs = plt.subplots(2, 3, figsize=(10, 5))  
    metrics = ['time', 'MFU', 'sps']  
    link_types = ['PCIe 4', 'NVLink']  
      
    for i, metric in enumerate(metrics):  
        for j, link_type in enumerate(link_types):  
            ax = axs[i // 3 + j, i % 3]  # 计算轴的位置，基于2x3的网格  
            if ax is not None:  # 确保我们不会尝试访问不存在的轴（在这个例子中不会发生）  
                x_labels = [d['dp+pp+tp'] for d in data[link_type]]  
                y_values = [d[metric] for d in data[link_type]]  
                ax.set_title(f'{link_type} {metric}')  
                ax.set_xlabel('dp+pp+tp')  
                ax.set_ylabel(metric)  
                ax.bar(x_labels, y_values)  
      
    # 调整布局以去除多余的空白  
    plt.tight_layout()  
    plt.show()  
  
# 调用函数绘制所有图表  
plot_all_metrics()