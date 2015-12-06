# minphone makefile test
PWD:=$(shell pwd)

TARGET = exe

objs:=$(patsubst %.c,%.o,$(wildcard *.c))
objs+=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
#objs += libsqlite3.a

CC:=gcc
CXX:=g++
#CC=arm-linux-gcc


CFLAGS = -Wall -g
#LDFLAFS = -ldl -lpthread


$(TARGET) : $(objs) $(LDFLAFS)
	$(CXX) $(CFLAGS)  $^ -o $@

.PHONY:tags cscope clean
# cscope & ctags 
tags:
	ctags -R
cscope:
	cscope -R
clean:
	@-rm -rf exe $(objs) tags cscope*


