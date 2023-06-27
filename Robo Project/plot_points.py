import matplotlib.pyplot as plt

#Plots the points from the coordinates
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
    
# Opening the file
file = open("out.txt", 'r')

# x and y coordinates of the robot
content = file.readlines()
x = [num.strip() for num in content[0].split(' ')]
y = [num.strip() for num in content[1].split(' ')]
getPoints(x, y)

# Showing the plot
plt.show()
    
