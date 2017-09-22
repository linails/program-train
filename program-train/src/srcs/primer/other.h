/*
 * Progarm Name: other.h
 * Created Time: 2016-03-11 15:16:37
 * Last modified: 2017-09-22 11:28:14
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _OTHER_H_
#define _OTHER_H_

/*other test*/
extern void other_test(void);

extern void do_pcb(void (*pf)(void));

class OtherTest{
public:
    OtherTest();
    ~OtherTest();
    int  main(void);
private:
    int  macro_test(void);
};

#endif //_OTHER_H_

