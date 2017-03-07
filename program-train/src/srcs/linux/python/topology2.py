#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-08 09:30:27
#

import networkx as nx
#import pylab as plt
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import numpy as np
from scipy.integrate import odeint

fig = plt.figure()
ax = fig.gca(projection = '3d')

#g = nx.Graph()

#g.add_edge(1, 2, weight = 4)
#g.add_edge(1, 3, weight = 7)
#g.add_edge(1, 4, weight = 8)
#g.add_edge(1, 5, weight = 3)
#g.add_edge(1, 9, weight = 3)

#g.add_edge(1, 6, weight = 6)
#g.add_edge(6, 7, weight = 7)
#g.add_edge(6, 8, weight = 7)

#g.add_edge(6, 9, weight = 6)
#g.add_edge(9, 10, weight = 7)
#g.add_edge(9, 11, weight = 6)

#fixed_pos = {1:(1, 1),\
#             2:(0.7, 2.2),\
#             3:(0, 1.8),\
#             4:(1.6, 2.3),\
#             5:(2, 0.8),\
#             6:(-0.6, -0.6),\
#             7:(-1.3, 0.8),\
#             8:(-1.5, -1),\
#             9:(0.5, -1.5),\
#             10:(1.7, -0.8),\
#             11:(1.5, -2.3),\
#             }

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

#nx.draw_networkx_nodes(g, pos = fixed_pos, nodelist=[1, 2, 3, 4, 5], node_color = 'g', node_size = 300)
#nx.draw_networkx_edges(g, pos = fixed_pos, edgelist=[(1, 2), (1, 3), (1, 4), (1, 5), (1, 9)], edge_color = 'g', \
#        width = [1.5, 1.5, 1.5, 1.5, 1.5], label = [1, 2, 3, 4, 5], node_size = 300)

#nx.draw_networkx_nodes(g, pos=fixed_pos, nodelist=[6, 7, 8], node_color = 'r', node_size=300)
#nx.draw_networkx_edges(g, pos=fixed_pos, edgelist=[(6, 7), (6, 8), (1, 6)], width = [1.5, 1.5, 1.5], edge_color=\
#        'r', node_size = 300)


#nx.draw_networkx_nodes(g, pos=fixed_pos, nodelist=[9, 10, 11], node_color = 'b', node_size=300)
#nx.draw_networkx_edges(g, pos=fixed_pos, edgelist=[(6, 9), (9, 10), (9, 11)], width = [1.5, 1.5, 1.5], edge_color=\
#        'b', node_size = 300)

#plt.text(fixed_pos[1][0], fixed_pos[1][1]+0.2, s = '1', fontsize = 15)
#plt.text(fixed_pos[2][0], fixed_pos[2][1]+0.2, s = '2', fontsize = 15)
#plt.text(fixed_pos[3][0], fixed_pos[3][1]+0.2, s = '3', fontsize = 15)
#plt.text(fixed_pos[4][0], fixed_pos[4][1]+0.2, s = '4', fontsize = 15)
#plt.text(fixed_pos[5][0], fixed_pos[5][1]+0.2, s = '5', fontsize = 15)
#plt.text(fixed_pos[6][0], fixed_pos[6][1]+0.2, s = '6', fontsize = 15)
#plt.text(fixed_pos[7][0], fixed_pos[7][1]+0.2, s = '7', fontsize = 15)
#plt.text(fixed_pos[8][0], fixed_pos[8][1]+0.2, s = '8', fontsize = 15)
#plt.text(fixed_pos[9][0], fixed_pos[9][1]+0.2, s = '9', fontsize = 15)
#plt.text(fixed_pos[10][0], fixed_pos[10][1]+0.2, s = '10', fontsize = 15)
#plt.text(fixed_pos[11][0], fixed_pos[11][1]+0.2, s = '11', fontsize = 15)

data = [(0, 0, 0)]

for f in fixed_pos:
    print "f =", f
    print "fixed_pos[%d] =" %f, fixed_pos[f]
    data.append(fixed_pos[f])
    x = fixed_pos[f][0]
    y = fixed_pos[f][1]
    z = fixed_pos[f][2]
    print "(x, y) = (%d, %d), "% (x, y)
    ax.scatter(x, z, y, zdir = 'y', c='r')

#x = np.linspace(0, 1, 100)
#y = np.sin(x*2*np.pi) / 2 + 0.5
#ax.plot(x, y, zs=0, zdir='z', label='zs=0, zdir=z')

#ax.plot3(fixed_pos[0], fixed_pos[1])
#ax.plot_surface(fixed_pos[0], fixed_pos[1], rstride=2, cstride=1,cmap=plt.cm.coolwarm,alpha=0.8)

#X, Y, Z = axes3d.get_test_data(0.1)

X = [[-1, 0, 1],[-1, 0, 1],[-1, 0, 1]]
Y = [[-1, 0, 1],[-1, 0, 1],[-1, 0, 1]]
Z = [[-1, 0, 1],[-1, 0, 1],[-1, 0, 1]]

print "data =", data

#print "fixed_pos[0] =", fixed_pos[0]
#print "fixed_pos[1] =", fixed_pos[1]
#print "fixed_pos[2] =", fixed_pos[2]

#X = [data[0],data[1], data[2], data[3], data[4], data[5]]
#Y = [data[5],data[4], data[3], data[2], data[1], data[0]]
#Z = [data[3],data[1], data[2], data[5], data[4], data[0]]

print "x =", X
print "y =", Y
print "Z =", Z

print "type(X) :", type(X)
#print "X[:, 0] =", X[:, 0]
x1=[]
x2=[]
x3=[]

for xs in X:
    #x1.append(xs)
    print "xs = ", xs
    x1.append(xs[0])
    x2.append(xs[1])
    x3.append(xs[2])

print "x1 =", x1

y1=[]
y2=[]
y3=[]

for xs in Y:
    #x1.append(xs)
    print "xs = ", xs
    y1.append(xs[0])
    y2.append(xs[2])
    y3.append(xs[1])

print "y1 =", y1

#ax.plot_wireframe(X, Y, Z, rstride=5, cstride=5)
#ax.plot(x1, x2, x3)
#ax.plot(y1, y2, y3)

#ax.plot([1, 2, 0], [1, 2, 0], [0, 0, 0],  'go-', label='line 1', linewidth=2)
#ax.plot([1, 2], [1, 2], [0, 0], 'ro-', label='line 1', linewidth=2)
#ax.plot([1, 2, 3], [1, 2, 3], 'ro-', label='line 1', linewidth=2)
#ax.plot([1, 2, 3], [1, 2, 3], [0, 0, 0],  'go-', label='line 2', linewidth=2)

def draw_edge(p1, p2):
    #ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro-', label='line 1', linewidth=2)
    ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'ro-', linewidth=2)

def tag_info(point, s):
    ax.text(point[0], point[1], point[2], s, fontsize=8)

p1 = (1, 1, 0)
p2 = (2, 2, 0)

draw_edge(p1, p2)

draw_edge(data[0], data[1])
draw_edge(data[1], data[2])

tag_info(data[0], '0x0000\nmac:')
tag_info(data[1], '0x0001\nmac:')
tag_info(data[2], '0x0002\nmac:')

def lorenz(w, t, p, r, b):
    x, y, z = w.tolist()
    return p * (y - x), x * (r - z), x * y - b * z

t = np.arange(0, 30, 0.01)

track1 = odeint(lorenz, (0.0, 1.00, 0.0), t, args=(10.0, 28.0, 3.0))
track2 = odeint(lorenz, (0.0, 1.01, 0.0), t, args=(10.0, 28.0, 3.0))

print "track1 =", track1
print "track2 =", track2
print "-------------------------------------"
print "track1[:, 0] =", track1[:, 0]
print "track1[:, 1] =", track1[:, 1]
print "track1[:, 2] =", track1[:, 2]

#ax.plot(track1[:, 0], track1[:, 1], track1[:, 2])
#ax.plot(track2[:, 0], track2[:, 1], track2[:, 2])


ax.legend()
ax.set_xlim3d(-20, 30)
ax.set_ylim3d(-20, 30)
ax.set_zlim3d(-20, 30)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

