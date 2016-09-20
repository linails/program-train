/*
 * Progarm Name: linux_main.cpp
 * Created Time: 2016-08-24 09:17:33
 * Last modified: 2016-09-20 11:05:04
 * @author: minphone.linails linails@foxmail.com 
 */

#include "linux_main.h"
#include <iostream>
#include "sys_cmd.hpp"

using namespace std;

void linux_main(void)
{
    cout << "------------- linux_main --------------" << endl;
    {
        sys_cmd_called();
    }
    cout << "---------------------------" << endl;
}

