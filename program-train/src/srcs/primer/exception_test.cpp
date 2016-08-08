/*
 * Progarm Name: exception_test.cpp
 * Created Time: 2016-08-07 21:27:27
 * Last modified: 2016-08-07 22:07:56
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exception_test.h"
#include <iostream>
#include <cstdio>
#include <stdexcept>

using namespace std;

void exception_test(void)
{
    cout << "---------- exception_test ----------" << endl;

    {
        try{
            {
                /* 可以逐级向外层传递 */
                try{

                    int a;

                    cout << "please input a num : " << endl;
                    cin >> a;
                    if(a < 20){
                        cout << "before throw" << endl;
                        throw runtime_error("ERROR : a < 20");
                        cout << "after throw" << endl;
                    }
                }
                catch(runtime_error err){
                    cout << err.what() << endl;
                    throw runtime_error(err.what());
                }
            }

        }
        catch(runtime_error err){
            cout << "catch error !" << endl;
            cout << err.what() << endl;
        }
        catch(...){
        }
    }
}

