#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-07 23:11:51
#

import os
import networkx as nx
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

G = nx.Graph()

G.add_node(0x0000)
G.add_node(0x0001)
G.add_node(0x0002)
G.add_node(0x0003)
G.add_node(0x0004)
G.add_node(0x0005)
G.add_edge(0x0000, 0x0001);
G.add_edge(0x0000, 0x0002);
G.add_edge(0x0001, 0x0003);
G.add_edge(0x0000, 0x0004);
G.add_edge(0x0003, 0x0005);

def print_info():
    print "Graph info"
    print G.nodes()
    print G.edges()
    print G.number_of_edges()

nx.draw(G)
plt.xlim(-1, 3)
plt.ylim(3, -1)
#plt.zlim(-2, 3)
plt.show()

