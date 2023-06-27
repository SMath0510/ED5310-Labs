import matplotlib.pyplot as plt
import numpy as np    

# Plots a line from slope and intercept
def abline(slope, intercept):
    axes = plt.gca()
    x_vals = np.array(axes.get_xlim())
    y_vals = intercept + slope * x_vals
    plt.plot(x_vals, y_vals, '--')

# Opening the output file
file = open("out.txt", 'r')

# Line 1
content = file.readlines()
x = content[2].split(" ")
slope = (float(x[0]))
intercept = (float(x[1]))
abline(slope, intercept)

# Line 2
x = content[3].split(" ")
slope = (float(x[0]))
intercept = (float(x[1]))
abline(slope, intercept)

# Showing the plot
plt.show()

