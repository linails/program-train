/*
 * Progarm Name: template_test.h
 * Created Time: 2016-02-02 16:38:46
 * Last modified: 2016-04-04 16:19:16
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#ifndef _TEMPLATE_TEST_H_
#define _TEMPLATE_TEST_H_

template <typename T>
inline T const &max(T const &a,T const &b)
{
    return a < b ? b : a;
}

extern void template_test(void);

#endif //_TEMPLATE_TEST_H_

