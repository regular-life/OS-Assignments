import matplotlib.pyplot as plt

f = open("file.txt", "r")
list_values = {'SCHED_FIFO': [], 'SCHED_RR': [], 'SCHED_OTHER': []}

for x in f:
    arr = x.split()
    if arr[0] in list_values:
        list_values[arr[0]] = float(arr[1])

f.close()

x_labels = range(1)

plt.plot(x_labels, list_values['SCHED_FIFO'], label='SCHED_FIFO')
plt.plot(x_labels, list_values['SCHED_RR'], label='SCHED_RR')
plt.plot(x_labels, list_values['SCHED_OTHER'], label='SCHED_OTHER')

plt.xlabel('Scheduling Policy')
plt.ylabel('Time')
plt.legend()

plt.show()
