#!/usr/bin/env python3
import matplotlib.pyplot as plt

'''
单机单卡测试（模式）	内存占用(MB)	单词迭代时间(S)	利用率MFU
64mbs+64gbs	47762	0.704	0.669969124397463
32mbs+64gbs	25006	0.731	0.6452233427849712
16mbs+64gbs	13638	0.753	0.6263721959838167
8mbs+64gbs	8004	1.116	0.42263285266649986
4mbs+64gbs	5096	1.997	0.23618340689825432
2mbs+64gbs	4052	3.745	0.12594346156897565
1mbs+64gbs	3280	7.029	0.06710175893808705
'''
y_mem = [3280, 4052, 5096, 8004, 13638, 25006, 47762]
y_time = [7.029, 3.745, 1.997, 1.116, 0.753, 0.731, 0.704]
y_MFU = [0.06710175893808705, 0.12594346156897565, 0.23618340689825432, 0.42263285266649986, 0.6263721959838167, 0.6452233427849712, 0.669969124397463]
x_lable = ['1', '2', '4', '8', '16', '32', '64']

# 创建一个1*3的子图
fig, axs = plt.subplots(1, 3, figsize=(15, 5))
# 第一个子图
axs[0].bar(x_lable, y_mem, label='Memory usage')
axs[0].set_title('Memory usage of different models')
axs[0].set_xlabel('mbs')
axs[0].set_ylabel('Memory usage(MB)')
axs[0].legend(title="Memory", loc='upper left')
# 第二个子图
axs[1].bar(x_lable, y_time, label='Time')
axs[1].set_title('Time of different models')
axs[1].set_xlabel('mbs')
axs[1].set_ylabel('Time(S)')
axs[1].legend(title="Time", loc='upper right')
# 第三个子图
axs[2].bar(x_lable, y_MFU, label="MFU")
axs[2].set_title('MFU of different models')
axs[2].set_xlabel('mbs')
axs[2].set_ylabel('MFU')
axs[2].set_ylim(0,1)
axs[2].legend(title='MFU', loc='upper right')
# 显示每个数据的具体值
for i, v in enumerate(y_mem):
    axs[0].text(i, v + 500, str(v), ha='center')
for i, v in enumerate(y_time):
    axs[1].text(i, v + 0.1, str(v), ha='center')
for i, v in enumerate(y_MFU):
    # 将i 格式转变为4位小数
    v = format(v, '.3f')
    axs[2].text(i, float(v) + 0.01, str(v), ha='center')

plt.show()
