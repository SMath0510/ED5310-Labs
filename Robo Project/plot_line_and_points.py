import matplotlib.pyplot as plt
import numpy as np    

# Plots a graph from slope and intercept
def abline(slope, intercept):
    axes = plt.gca()
    x_vals = np.array(axes.get_xlim())
    y_vals = intercept + slope * x_vals
    plt.plot(x_vals, y_vals, '--')

# Plots the points from the coordinates
def getPoints(x, y):
    X = []
    Y = []
    for num in x:
        if num != '':
            X.append((float)(num))
    for num in y:
        if num != '':
            Y.append((float)(num))
    plt.scatter(X, Y)
     
# Opens the file
file = open("out.txt", 'r')

# x and y coordinates of the robot
content = file.readlines()
x = [num.strip() for num in content[0].split(' ')]
y = [num.strip() for num in content[1].split(' ')]
getPoints(x, y)
print(x)
print(y)

# Line 1
l1 = [num.strip() for num in content[2].split(' ')]
slope = (float(l1[0]))
intercept = (float(l1[1]))
abline(slope, intercept)

# Line 2
l2 = [num.strip() for num in content[3].split(' ')]
slope = (float(l2[0]))
intercept = (float(l2[1]))
abline(slope, intercept)

# Showing the plot
plt.show()

