/*
 * Progarm Name: mqueue.hpp
 * Created Time: 2017-01-03 15:01:58
 * Last modified: 2017-01-06 16:51:39
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MQUEUE_HPP_
#define _MQUEUE_HPP_

class mQueue{
public:
    mQueue();
    ~mQueue();
    int  mqueue_main(int argc, char **argv);
private:
    int  circ_queue(void);
};

#endif //_MQUEUE_HPP_

