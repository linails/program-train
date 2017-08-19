/*
 * Progarm Name: backtrace.hpp
 * Created Time: 2017-08-18 23:25:12
 * Last modified: 2017-08-19 14:25:15
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _BACKTRACE_HPP_
#define _BACKTRACE_HPP_

#define BT_DEPTH 32

class Backtrace{
public:
    Backtrace();
    ~Backtrace();
    int  segmentfault_test(void);
private:
    static void bt_dump(int signo);
};

#endif //_BACKTRACE_HPP_

