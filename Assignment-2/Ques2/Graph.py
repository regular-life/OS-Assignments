import matplotlib.pyplot as plt
import numpy as np

f = open("file.txt", "r")
list_values = {'SCHED_FIFO': 0, 'SCHED_RR': 0, 'SCHED_OTHER': 0}

for x in f:
    arr = x.split()
    if arr[0] in list_values:
        list_values[arr[0]] = float(arr[1])

f.close()

plt.bar(1, list_values['SCHED_FIFO'], label='SCHED_FIFO')
plt.bar(2, list_values['SCHED_RR'], label='SCHED_RR')
plt.bar(3, list_values['SCHED_OTHER'], label='SCHED_OTHER')

plt.xlabel('Scheduling Policy')
plt.ylabel('Time')
plt.legend()

plt.show()
