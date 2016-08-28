/*
 * Progarm Name: overload.cpp
 * Created Time: 2016-02-02 17:01:21
 * Last modified: 2016-08-24 09:41:05
 */

#include "overload.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Oprt{
public:
    Oprt():x(10){};
    ~Oprt(){};
    void print(void){cout << "x = " << x << endl;};
    int *operator~(){cout << "operator~" << endl; return &x;};
private:
    int x;
};

Oprt& operator*(const Oprt& a, const Oprt& b)
{
    return (Oprt &)a;
}

/*overload_test*/
void overload_test(void)
{
    cout << "------------ overload_test ! ------------" << endl;
    {
        /* 重载操作符必须具有至少一个类类型或枚举类型的操作数 
         *
         * 这条规则强制重载操作符不能重新定义用于内置类型的操作符的含义
         * */
        Oprt o;
        int *p = ~o;
        cout << "*p = " << *p << endl;

        /* { + , - , * , & }有四个符号，即可作一元操作符又可作二元操作符 */
    }
}



