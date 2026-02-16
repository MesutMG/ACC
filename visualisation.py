from matplotlib import pyplot as plt
from pprint import pprint

file = open("./vehicle_status.csv","r")

line = file.readline() #skipping first line since it's just text

line = file.readline() #starts from the data
lines = []
linesT = [[] for _ in range(len(line.split(",")))]  #for transposed

while line:
    words = line.split(",") #csv seperation
    words[-1] = words[-1][:-2:] #removing \n at the end of the last element

    for i in range(len(words)):
        words[i] = float(words[i])
        linesT[i].append(words[i])
        
    lines.append(words)
    line = file.readline()

plt.plot(linesT[4],linesT[0])
plt.show()