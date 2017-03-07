#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-08 17:19:55
#

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d

#draw a vector
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d




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


def arrow_flow(ax, points, direct=True, clr='r'):
    class Arrow3D(FancyArrowPatch):
        def __init__(self, xs, ys, zs, *args, **kwargs):
            FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
            self._verts3d = xs, ys, zs

        def draw(self, renderer):
            xs3d, ys3d, zs3d = self._verts3d
            xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
            self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
            FancyArrowPatch.draw(self, renderer)

    def test(ax):
        vpoints = [(1, 1, 1),\
                   (0.7, 2.2, 1),\
                   (0, 1.8, 3),\
                   (1.6, 2.3, -1),\
                   (2, 0.8, 3),\
                   (-0.6, -0.6, 2),\
                   (-1.3, 0.8, 2),\
                   (-1.5, -1, 0.3),\
                   (0.5, -1.5, 2),\
                   (1.7, -0.8, 1),\
                   (1.5, -2.3, 0),\
                   ]

        varrow = []

        astyle = '->'

        if direct == True:
            astyle = '->'
        else:
            astyle = '<-'

        for idx in range(len(vpoints) - 1):
            varrow.append(
                Arrow3D([vpoints[idx][0],vpoints[idx+1][0]],
                        [vpoints[idx][1],vpoints[idx+1][1]],
                        [vpoints[idx][2],vpoints[idx+1][2]], mutation_scale=20, lw=2, arrowstyle=astyle, color=clr)
            )

        [ax.add_artist(arr) for arr in varrow]

    test(ax)



times = 0

def draw_point(points, draw=False):
    global times
    for f in points:
        if draw == False:
            data.append(points[f])
        x = points[f][0]
        y = points[f][1]
        z = points[f][2]
        if times % 2 == 1:
            #ax.scatter(x, y, z, zdir = 'z', s=50 , c='b', marker = '*')
            ax.scatter(x, y, z, zdir = 'z', s=20 , c='b')
        else:
            ax.scatter(x, y, z, zdir = 'z', s=20 , c='r')
        times += 1


def draw_edge(p1, p2):
    #ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro--', linewidth=2)
    global times
    if times % 2 == 1:
        ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ko-', linewidth=2)
    else:
        ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ko-.', linewidth=2, markersize=5)
    times += 1
    #ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ko-')
    #ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro--', **marker_style)
    #ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro-.', **marker_style)
    #ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro:', **marker_style)

def tag_info(point, s):
    tag = '\n'.join(s)
    ax.text(point[0], point[1], point[2], tag)

draw_point(fixed_pos)

arrow_flow(ax, fixed_pos)

#draw_edge(data[0], data[1])
#draw_edge(data[1], data[2])
#draw_edge(data[0], data[2])

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

plt.show()


