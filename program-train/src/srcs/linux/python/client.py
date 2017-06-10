#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2017-03-08 20:29:45
# Last modified: 2017-03-08 20:54:31
# 

import socket
import time

s = socket.socket()

host = socket.gethostname()
port = 9190 

s.connect((host, port))

times = 0
while True:
    s.send("nict to meet you")
    data = s.recv(1024)
    print "data = %s - %d"%(data, times)
    time.sleep(0.001)
    times += 1


