import matplotlib.pyplot as plt
import json

x = []
y = []
with open('parallel_accum/sum 1000000000.json') as json_file:
    data = json.load(json_file)
    for i in data["number of threads"]:
        x.append(i)
    for t in data["time"]:
        y.append(t)
    fig, ax = plt.subplots()
    plt.suptitle("")
    ax.plot(x, y, marker='.', markersize=10)
    ax.set_ylabel("time")
    ax.set_xlabel("number of threads")
    plt.show()

