#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-09 14:14:50
#

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from pprint import pprint
from mpl_toolkits.mplot3d import axes3d


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

data = []

fig = plt.figure()
ax = fig.gca(projection = '3d')

print "ax :", ax
pprint(ax)

def draw_point(points, draw=False):
    for f in points:
        if draw == False:
            data.append(points[f])
        x = points[f][0]
        y = points[f][1]
        z = points[f][2]
        pprint(ax.scatter(x, y, z, zdir = 'z', s=20 , c='r'))

def draw_edge(p1, p2):
    #ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro--', linewidth=2)
    pprint(ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro-', linewidth=2))

def tag_info(point, s):
    tag = '\n'.join(s)
    ax.text(point[0], point[1], point[2], tag)

draw_point(fixed_pos)

draw_edge(data[0], data[1])
draw_edge(data[1], data[2])
draw_edge(data[0], data[2])

#tag_info(data[0], ['0x0000','mac:'])
#tag_info(data[1], ['0x0001','mac:'])
#tag_info(data[2], ['0x0002','mac:'])

def tag_test():
    tag_info(data[0], ['1'])
    tag_info(data[1], ['2'])
    tag_info(data[2], ['3'])
    tag_info(data[3], ['4'])
    tag_info(data[4], ['5'])
    tag_info(data[5], ['6'])
    tag_info(data[6], ['7'])
    tag_info(data[7], ['8'])
    tag_info(data[8], ['9'])
    tag_info(data[9], ['10'])
    tag_info(data[10], ['11'])

tag_test()

ax.legend()
ax.set_xlim3d(-2, 3)
ax.set_ylim3d(-2, 3)
ax.set_zlim3d(-2, 3)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

ax.set_title('Zigbee Network')

plt.show()



