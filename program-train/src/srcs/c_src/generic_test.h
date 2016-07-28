/*
 * Progarm Name: generic_test.h
 * Created Time: 2016-07-11 11:36:07
 * Last modified: 2016-07-11 14:43:00
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#ifndef _GENERIC_TEST_H_
#define _GENERIC_TEST_H_

extern void generic_test(void);

/* function template 
 * template 后接模板形参表 */
template <typename T>
int compare(const T &v1, const T &v2)
{
    if(v1 < v2) return -1;
    if(v2 < v1) return  1;
    return 0;
}



#endif //_GENERIC_TEST_H_

