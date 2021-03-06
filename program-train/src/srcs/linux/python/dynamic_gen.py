#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-09 11:02:56
#

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig = plt.figure()
axes1 = fig.add_subplot(111)
line, = axes1.plot(np.random.rand(10))

def update(data):
    line.set_ydata(data)
    return line,

def data_gen():
    while True:
        yield np.random.rand(10)

ani = animation.FuncAnimation(fig, update, data_gen, interval=1 * 1000)

plt.show()

