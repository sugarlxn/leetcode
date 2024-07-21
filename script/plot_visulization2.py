#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
import json


data = []
batch_size = [2, 4, 8, 16, 32, 64]

mode_114 = {
    'mode' : '114',
    'batch_size' : batch_size,
    'samples_per_sceond' : [943, 1748, 2459, 3533, 3831, 3761],
    'MFU' : [0.0172, 0.0322, 0.0453, 0.0651, 0.0705, 0.0693]
}
mode_122 = {
    'mode' : '122',
    'batch_size' : batch_size,
    'samples_per_sceond' : [716,1412,2780,4801,7036,9060],
    'MFU' : [0.0131, 0.0260, 0.0512, 0.0884, 0.1296, 0.1669]
}
'''
samples per sceond	MFU
545	0.0100
1143	0.0210
1959	0.0361
3528	0.0650
5375	0.0990
7088	0.1305
'''
mode_141 = {
    'mode' : '141',
    'batch_size' : batch_size,
    'samples_per_sceond' : [545, 1143, 1959, 3528, 5375, 7088],
    'MFU' : [0.0100, 0.0210, 0.0361, 0.0650, 0.0990, 0.1305]
}

'''
samples per sceond	MFU
1721	0.0317
3543	0.0653
6849	0.1262
11515	0.2122
15162	0.2794
'''
mode_212 = {
    'mode' : '212',
    'batch_size' : batch_size,
    'samples_per_sceond' : [1721, 3543, 6849, 11515, 15162],
    'MFU' : [0.0317, 0.0653, 0.1262, 0.2122, 0.2794]

}

"""
samples per sceond	MFU
1425	0.0262
2837	0.0523
5476	0.1009
8886	0.1637
12284	0.2263
"""
mode_221 = {
    'mode' : '221',
    'batch_size' : batch_size,
    'samples_per_sceond' : [1425, 2837, 5476, 8886, 12284],
    'MFU' : [0.0262, 0.0523, 0.1009, 0.1637, 0.2263]
}

'''
samples per sceond	MFU
5051	0.0931
5774	0.1064
12190	0.2246
20356	0.3750
27356	0.5040
'''
mode_411 = {
    'mode' : '411',
    'batch_size' : batch_size,
    'samples_per_sceond' : [5051, 5774, 12190, 20356, 27356],
    'MFU' : [0.0931, 0.1064, 0.2246, 0.3750, 0.5040]
}

data.append(mode_114)
data.append(mode_122)
data.append(mode_141)
# data.append(mode_212)
# data.append(mode_411)
# data.append(mode_221)

# 创建一个2*3的子图
fig, axs = plt.subplots(1,3,figsize=(15,10))
index = 0
for mode in data:
    # 第一个子图
    axs[index%3].bar(mode['batch_size'], mode['samples_per_sceond'], label='samples_per_sceond')
    axs[index%3].set_title(f'samples_per_sceond of mode{mode["mode"]}')
    axs[index%3].set_xlabel('batch_size')
    axs[index%3].set_ylabel('samples_per_sceond')
    axs[index%3].legend(title='samples_per_sceond', loc='upper left')
    # 显示每个数据的具体值
    for i, v in enumerate(mode['samples_per_sceond']):
        axs[index%3].text(i, v + 500, str(v), ha='center')
    index += 1
plt.show()

