/*
 * Progarm Name: template_test.h
 * Created Time: 2016-02-02 16:38:46
 * Last modified: 2016-08-08 21:49:37
 * @author: minphone.linails linails@foxmail.com 
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

