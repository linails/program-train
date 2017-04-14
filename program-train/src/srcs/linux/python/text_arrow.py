#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-31 14:59:50
# Last modified: 2016-10-31 17:14:06
# 

import numpy as np
import matplotlib.pyplot as plt

def f1(t):
    return np.exp(-t)*np.cos(2*np.pi*t)

def f2(t):
    return np.sin(2*np.pi*t)*np.cos(3*np.pi*t)

t = np.arange(0.0,5.0,0.02)

plt.figure(figsize=(8,7))
p1 = plt.subplot(211)
p2 = plt.subplot(212)

label_f1 = "$f(t)=e^{-t} \cos (2 \pi t)$"
label_f2 = "$g(t)=\sin (2 \pi t) \cos (3 \pi t)$"

p1.plot(t,f1(t),"g-",label=label_f1)
p2.plot(t,f2(t),"r-.",label=label_f2,linewidth=2)

p1.axis([0.0,5.01,-1.0,1.5])

p1.set_ylabel("v",fontsize=14)
p1.set_title("A simple example",fontsize=18)
p1.grid(True)
#p1.legend()

tx = 2
ty = 0.9
p1.text(tx,ty,label_f1,fontsize=15,verticalalignment="top",horizontalalignment="right")

p2.axis([0.0,5.01,-1.0,1.5])
p2.set_ylabel("v",fontsize=14)
p2.set_xlabel("t",fontsize=14)
#p2.legend()

tx = 2
ty = 0.9
p2.text(tx,ty,label_f2,fontsize=15,verticalalignment="bottom",horizontalalignment="left")

p2.annotate('',xy=(2.8,0.5),xytext=(tx,ty), arrowprops=dict(arrowstyle="->",connectionstyle="arc3"))

plt.show()

