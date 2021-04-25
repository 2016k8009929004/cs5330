import matplotlib.pyplot as plt
import numpy as np
import os
from subprocess import Popen, PIPE
from operator import add
import palettable
import matplotlib
import re

x_label = 'Probing Array Size(log)'
y_label = 'Average Time(ns)'
x_tick_labels = ['5', '6', '7', '8']
# x_tick_labels = ['am', 'yt', 'up', 'eu', 'ac', 'ab', 'lj', 'ot', 'wk', 'uk', 'tw', 'fs', ]
x = range(0, 4)
# x = [10**5, 10**6, 10**7, 10**8]
line_legends = ['Simple', 'Twisted', 'Double', ]
line_markers = ['*', 'x', '^', 'o', '.']
line_colors = ['C0', 'C1', 'C2', 'C3', 'C4']


def draw_lines(line_data, path, y_min, y_max, is_log=False):
    plt.figure(figsize=(7, 4.2))

    for i in range(0, len(line_data)):
        plt.plot(x, line_data[i], label=line_legends[i],
                 color=line_colors[i], marker=line_markers[i], markersize=10, fillstyle='none',
                 linestyle='--')

    if is_log:
        plt.yscale('log')
    plt.minorticks_off()
    plt.xlabel(x_label, fontsize=18)
    plt.ylabel(y_label, fontsize=18)
    plt.xticks(x, x_tick_labels, fontsize=18)
    plt.yticks(fontsize=18)

    plt.ylim(y_min, y_max)
    plt.xlim(min(x) - 0.25, max(x) + 0.25)
    plt.legend(loc=0, ncol=3, fontsize=18, frameon=False, handletextpad=0.1, columnspacing=1.0, handlelength=1.5)
    plt.grid()
    plt.tight_layout()
    # plt.show()
    plt.savefig(path)
    plt.close()


def get_data(file_path, flag):
    text = open(file_path).read()
    pattern = [
        "(hash time is )(\s*)(\d+\.?\d*)",
        "(insert time is )(\s*)(\d+\.?\d*)",
        "(delete time is )(\s*)(\d+\.?\d*)",
        "(step is )(\s*)(\d+\.?\d*)",
    ]
    match = re.findall(pattern[flag], text)
    if len(match) == 0:
        return 0
    result = float(match[-1][2])
    return result


result_path = '/home/yuhang/Work/cs5330/results/linear_probing'

input_file_path_format = result_path + '/{0}'

input_file_list = [
    'linear_probing_simple_100000_10000.res',
    'linear_probing_simple_1000000_100000.res',
    'linear_probing_simple_10000000_1000000.res',
    'linear_probing_simple_100000000_10000000.res',
    'linear_probing_twisted_100000_10000.res',
    'linear_probing_twisted_1000000_100000.res',
    'linear_probing_twisted_10000000_1000000.res',
    'linear_probing_twisted_100000000_10000000.res',
    'linear_probing_double_100000_10000.res',
    'linear_probing_double_1000000_100000.res',
    'linear_probing_double_10000000_1000000.res',
    'linear_probing_double_100000000_10000000.res',
]

avg_hash_time = np.zeros(shape=(3, 4))
avg_insert_time = np.zeros(shape=(3, 4))
avg_delete_time = np.zeros(shape=(3, 4))
avg_step_size = np.zeros(shape=(3, 4))

for i, input_file in enumerate(input_file_list):
    input_file_path = input_file_path_format.format(input_file)
    app_idx = i // 4
    size_idx = i % 4
    avg_hash_time[app_idx][size_idx] = get_data(input_file_path, 0)
    avg_insert_time[app_idx][size_idx] = get_data(input_file_path, 1)
    avg_delete_time[app_idx][size_idx] = get_data(input_file_path, 2)
    avg_step_size[app_idx][size_idx] = get_data(input_file_path, 3)


print(avg_hash_time)
print(avg_insert_time)
print(avg_delete_time)
print(avg_step_size)

file_path = 'figures/linear_probing_avg_hash_time.pdf'
draw_lines(avg_hash_time, file_path, 10, 10**5, is_log=True)
file_path = 'figures/linear_probing_avg_insert_time.pdf'
draw_lines(avg_insert_time, file_path, 10, 10**5, is_log=True)
file_path = 'figures/linear_probing_avg_delete_time.pdf'
draw_lines(avg_delete_time, file_path, 10, 10**5, is_log=True)
# '''
