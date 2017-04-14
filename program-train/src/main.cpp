/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2017-04-14 23:54:49
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include <cassert>
#include "manager.hpp"
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    int ret = 0;

    string path;

    switch(argc){
        case 1:
            break;
        case 2:
            path = argv[1];
            break;
        case 3:
            cout << "[Warning] argc = 3" << endl;
            break;
    }

    Manager *pmgr = Manager::get_instance(new Manager(path));
    if(nullptr != pmgr){
        cout << "new successed" << endl;
    }else{
        cout << "[Error] new Manager() failed !" << endl;
    }

    ret = pmgr->main(argc, argv); assert(-1 != ret);

    delete pmgr;

    return ret;
}


