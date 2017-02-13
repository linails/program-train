/*
 * Progarm Name: mlinux.hpp
 * Created Time: 2016-12-21 09:39:08
 * Last modified: 2017-02-10 16:25:21
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MLINUX_HPP_
#define _MLINUX_HPP_

class mLinux{
public:
    mLinux();
    ~mLinux();
    int  mlinux_main(int argc, char **argv);
private:
    int  server(int argc, char **argv);
};

#endif //_MLINUX_HPP_

