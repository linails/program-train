#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-09 14:37:45
#

"""
A simple example of an animated plot... In 3D!
"""
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation
from pprint import pprint
import time
import threading


def Gen_RandLine(length, dims=2):
    """
    Create a line using a random walk algorithm

    length is the number of points for the line.
    dims is the number of dimensions the line has.
    """
    lineData = np.empty((dims, length))
    lineData[:, 0] = np.random.rand(dims)
    for index in range(1, length):
        # scaling the random numbers by 0.1 so
        # movement is small compared to position.
        # subtraction by 0.5 is to change the range to [-0.5, 0.5]
        # to allow a line to move backwards.
        step = ((np.random.rand(dims) - 0.5) * 0.1)
        lineData[:, index] = lineData[:, index - 1] + step

    return lineData

def ax_set_para():
    # Setting the axes properties
    ax.set_xlim3d([-2.0, 4.0])
    ax.set_xlabel('X')

    ax.set_ylim3d([-2.0, 4.0])
    ax.set_ylabel('Y')

    ax.set_zlim3d([-2.0, 4.0])
    ax.set_zlabel('Z')

    ax.set_title('Zigbee')


# Attaching 3D axis to the figure
fig = plt.figure()
ax = p3.Axes3D(fig)
ax_set_para()

#####################################################

# Fifty lines of random 3-D lines
data = [Gen_RandLine(25, 3) for index in range(50)]

print ""
print "data :", data
pprint(data)
print ""

# Creating fifty line objects.
# NOTE: Can't pass empty arrays into 3d version of plot()
lines = [ax.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1])[0] for dat in data]

print ""
print "lines :", lines
print ""

sindex = [0]
sindex0 = [2]

#----------------------------------------------------

fixed_pos = {1:(1, 1, 1),\
             2:(0.7, 2.2, 1),\
             3:(0, 1.8, 3),\
             4:(1.6, 2.3, -1),\
             5:(2, 0.8, 3),\
             6:(-0.6, -0.6, 2),\
             7:(-1.3, 0.8, 2),\
             8:(-1.5, -1, 0.3),\
             9:(0.5, -1.5, 2),\
             10:(1.7, -0.8, 1),\
             11:(1.5, -2.3, 0),\
             }

pdata = []

p0 = []
p1 = []
p2 = []

for idx in fixed_pos:
    p0.append(fixed_pos[idx][0])
    p1.append(fixed_pos[idx][1])
    p2.append(fixed_pos[idx][2])

pdata.append(p0)
pdata.append(p1)
pdata.append(p2)

pdata = [np.array(pdata)]

print "pdata :", pdata

points = [ax.scatter(p[0,0:0], p[1,0:0], p[2,0:0], zdir = 'z', s=20 , c='r') for p in pdata]
print "points :", points

plist = [12]

def update_points(num, pdata, points, ax, fig, plist, dataLines, lines):
    print "update_points :", num, "--- plist[0] :", plist[0]
    points = [ax.scatter(p[0,0:plist[0]], p[1,0:plist[0]], p[2,0:plist[0]], zdir = 'z', s=20 , c='r') for p in pdata]

    #allpoints = plt.getp(plt.gca(), 'points')
    #print "allpoints :", allpoints
    #pprint(allpoints)
    #print "plt.getp(ax.lines) :", plt.getp(ax.lines)
    #pprint(plt.getp(ax.lines))

    #print "fig :", fig
    #pprint(fig)

    plist[0] += 1
    if plist[0] >= 10:

        #if plist[0] >= 11:
        print "clear all * * * * * * * * * * *"
        plist[0] = 1
        ax.clear()
        ax.cla()
        ax_set_para()
        #else:
        #    lines = [ax.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1])[0] for dat in dataLines]
        #    for line, data in zip(lines, dataLines):
        #        # NOTE: there is no .set_data() for 3 dim data...
        ##        line.set_data(data[0:2, :25])
        #        line.set_3d_properties(data[2, :25])
        #        print "return lines============"
        #        return lines


        #print "plt.getp(fig.axes) :", plt.getp(fig.axes)
        #pprint(plt.getp(fig.axes))

        print "points clear"
        #points = [ax.scatter(p[0,0:11], p[1,0:11], p[2,0:11], zdir = 'z', s=0.1 , c='b', marker='.') for p in pdata]

    print "points :", points
    pprint(points)
    return points

def update_lines(num, dataLines, lines, si):
    print "si :", si[0]

    lines = [ax.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1],'b-')[0] for dat in dataLines]
    for line, data in zip(lines, dataLines):
        # NOTE: there is no .set_data() for 3 dim data...
        line.set_data(data[0:2, :25])
        line.set_3d_properties(data[2, :25])
        print "return lines============"
        return lines

# Creating the Animation object
line_ani = animation.FuncAnimation(fig, update_lines, 25, fargs=(data, lines, sindex),
                                   interval=1 * 1000, blit=False)

point_ani = animation.FuncAnimation(fig, update_points, plist[0], fargs=(pdata, points, ax, fig, plist,data, lines),
                                   interval=1 * 1000, blit=False)

#####################################################

#####################################################

print "rcParams :"
pprint(matplotlib.rcParams)

#print "fig :", fig
#pprint(fig)

#####################################################

plt.show()

while False:
    time.sleep(5)
    ax.cla()
    print "ax clear()"

