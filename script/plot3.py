import pandas as pd  
import matplotlib.pyplot as plt  
  
# 定义数据  
data = {  
    'Link speed (Gbps)': [10, 10, 10, 40, 40, 40, 100, 100, 100],  
    'dp+pp+tp': ['1+1+2', '1+2+1', '2+1+1', '1+1+2', '1+2+1', '2+1+1', '1+1+2', '1+2+1', '2+1+1'],  
    'Elapsed time per iteration (ms)': [3287.6, 877.0, 503.9, 1658.6, 813.9, 462.1, 1769.8, 806.6, 464.2],  
    'MFU': [7.2, 26.9, 46.8, 14.2, 29.0, 51.0, 13.3, 29.2, 50.8],  
    'Sample throughput (sps)': [1947, 7298, 12701, 3859, 7863, 13850, 3616, 7935, 13787],  
    'Peak bandwidth (Gbps)': [10.256, 10.349, 10.250, 40.636, 33.158, 16.720, 35.636, 33.283, 22.677],  
    'Total traffic (Gb)': [2870.947, 99.824, 107.423, 2868.514, 99.785, 107.350, 2868.507, 99.779, 107.382],  
    'Avg rate (Gbps)': [8.730, 1.138, 2.132, 17.295, 1.226, 2.323, 16.208, 1.237, 2.313]  
}  
  
# 将数据转换为DataFrame  
df = pd.DataFrame(data)  
  
# 设置图形大小  
plt.figure(figsize=(14, 18))  
  
# 继续之前的代码  
  
# 绘制每个度量指标的图表  
metrics = [  
    'Elapsed time per iteration (ms)',  
    'MFU',  
    'Sample throughput (sps)',  
    'Peak bandwidth (Gbps)',  
    'Total traffic (Gb)',  
    'Avg rate (Gbps)'  
]  
  
n_rows = 3  # 3行  
n_cols = 2  # 2列  
# 确保有足够的子图位置  
plt.subplots_adjust(hspace=0.5, wspace=0.3)  # 调整子图之间的水平和垂直间距  
  
for i, metric in enumerate(metrics):  
    # 计算子图的位置  
    row = i // n_cols  
    col = i % n_cols  
      
    # 创建一个新的子图（但实际上我们使用plt.subplot来重用之前的图形）  
    # 注意：由于我们已经使用plt.figure()创建了图形，所以我们不需要再次调用plt.subplots()  
    plt.subplot(n_rows, n_cols, i + 1)  
      
    # 设置子图的标题、x轴和y轴标签  
    plt.title(f'{metric} at Different dp+pp+tp Configurations')  
    plt.xlabel('dp+pp+tp')  
    plt.ylabel(metric)  
      
    # 遍历不同的Link speed，并为每个Link speed绘制一个条形图  
    for link_speed in df['Link speed (Gbps)'].unique():  
        subset = df[df['Link speed (Gbps)'] == link_speed]  
          
        # 为了区分不同的Link speed，我们可以使用不同的颜色或图案  
        # 这里我们简单地使用不同的颜色  
        colors = ['b', 'g', 'r', 'c', 'm', 'y']  # 假设有足够的颜色来区分（实际上可能不够用）  
          
        # 但在这个例子中，我们简化一下，只使用基本的颜色循环  
        color_index = (link_speed/10) % len(colors)  # 假设Link speed是10的倍数，并且不超过颜色数量  
        
        # 绘制条形图  
        plt.bar(subset['dp+pp+tp'], subset[metric], color=colors[int(color_index)], label=f'{link_speed} Gbps')  
      
    # 添加图例（可选，但在这里可能有助于区分不同的Link speed）  
    plt.legend(title='Link Speed (Gbps)')  
  
# 显示图形  
plt.tight_layout()  # 自动调整子图参数, 使之填充整个图像区域  
plt.show()  
  
# 注意：上面的颜色映射方法是简化的，实际上你可能需要为每个Link speed定义一个明确的颜色  
# 你可以使用一个字典来映射Link speed到颜色，如下所示：  

# 然后在绘制条形图时使用这个字典来获取颜色