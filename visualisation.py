from matplotlib import pyplot as plt
from pprint import pprint

file = open("./vehicle_status.csv","r")

line = file.readline() #skipping first line since it's just text

line = file.readline() #starts from the data
lines = []
linesT = [[] for _ in range(len(line.split(",")))]  #for transposed

while line:
    words = line.split(",") #csv seperation
    words[-1] = words[-1].strip() #removing \n at the end of the last element

    for i in range(len(words)):
        words[i] = float(words[i])
        linesT[i].append(words[i])
        
    lines.append(words)
    line = file.readline()

fig, axs = plt.subplots(2,2)
fig.suptitle('ACC System')
axs[0,0].plot(linesT[4],linesT[0])
axs[0,0].set(xlabel="Time (s)", ylabel="Velocity (m/s)")
axs[0,1].plot(linesT[4],linesT[1])
axs[0,1].set(xlabel="Time (s)", ylabel="Position (m)")
axs[1,0].plot(linesT[4], linesT[2])
axs[1,0].set(xlabel="Time (s)", ylabel = "Throttle")
axs[1,1].plot(linesT[4],linesT[3])
axs[1,1].set(xlabel="Time (s)", ylabel="State")

plt.show()