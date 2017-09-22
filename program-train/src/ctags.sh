#! /bin/sh
# Created Time: 2016-04-23 14:27:11
#

if [ "$#" != "0" ]; then
    ctags * -R $* --c++-kinds=+p --fields=+iaSl --extra=+q
else
    #ctags -R --c++-kinds=+p --fields=+iaS --extra=+q
    echo "ctag * -R xxxdir"
    ctags * -R \
              ./libs/ \
              ./main.cpp \
              ./srcs/advanced/ \
              ./srcs/algorithm/ \
              ./srcs/boost/ \
              ./srcs/cases/ \
              ./srcs/db/ \
              ./srcs/manager.cpp \
              ./srcs/manager.hpp \
              ./srcs/ooc/ \
              ./srcs/primer/ \
              ./srcs/sep/ \
              ./srcs/stl/ \
              ./srcs/tools/ \
              ./srcs/linux/io/ \
              ./srcs/linux/mlinux.cpp \
              ./srcs/linux/mlinux.hpp \
              ./srcs/linux/network/ \
              ./srcs/linux/os/ \
              ./srcs/linux/process/ \
              ./srcs/linux/server/ \
              ./srcs/linux/sys_cmd.cpp \
              ./srcs/linux/sys_cmd.hpp \
              ./srcs/linux/threads/ \
              --c++-kinds=+p --fields=+iaS --extra=+q
fi

