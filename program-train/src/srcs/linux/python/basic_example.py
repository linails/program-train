#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-09 13:50:18
#

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from pprint import pprint


def update_line(num, data, line):
    print ""
    print "update line ..."
    print "num :", num
    print "data :", data
    print "line :", line
    pprint(line)
    print ""
    line.set_data(data[..., :num])
    return line,

fig1 = plt.figure()

data = np.random.rand(2, 25)
l, = plt.plot([], [], 'b-')

print "l :", l
pprint(l)

plt.xlim(0, 1)
plt.ylim(0, 1)
plt.xlabel('x')
plt.title('test')

def test():
    print "test :", update_line(1, data, l)
    pprint(update_line(2, data, l))

line_ani = animation.FuncAnimation(fig1, update_line, 10, fargs=(data, l),
                                   interval=1 * 1000, blit=True)
#line_ani.save('lines.mp4')

#fig2 = plt.figure()

#x = np.arange(-9, 10)
#y = np.arange(-9, 10).reshape(-1, 1)
#base = np.hypot(x, y)
#ims = []
#for add in np.arange(15):
#    ims.append((plt.pcolor(x, y, base + add, norm=plt.Normalize(0, 30)),))
#
#im_ani = animation.ArtistAnimation(fig2, ims, interval=50, repeat_delay=3000,
#                                   blit=True)
#im_ani.save('im.mp4', metadata={'artist':'Guido'})

plt.show()
