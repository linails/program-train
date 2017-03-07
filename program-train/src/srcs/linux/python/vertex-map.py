#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-01 07:51:51
#

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

fig = plt.figure()
ax = fig.gca(projection='3d')

verts = [(0,0,0), (0,1,0), (1, 1, 0), (1, 0, 0), (0, 0, 1), (0, 1, 1), (1, 1, 1), (1, 0, 1)]
faces = [[0, 1, 2, 3], [4, 5, 6, 7], [0, 1, 5, 4], [1, 2, 6, 5], [2, 3, 7, 5], [0, 3, 7, 4]]

ploy3d = [[verts[vert_id] for vert_id in face] for face in faces]

x, y, z = zip(*verts)

ax.scatter(x, y, z)

ax.add_collection3d(Poly3DCollection(ploy3d, facecolors='r', linewidths=1, alpha=0.3))

ax.set_xlim3d(-0.5, 1.5)
ax.set_ylim3d(-0.5, 1.5)
ax.set_zlim3d(-0.5, 1.5)

plt.show()

