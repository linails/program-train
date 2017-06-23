/*
 * Progarm Name: finder.cpp
 * Created Time: 2017-06-05 14:24:09
 * Last modified: 2017-06-24 00:10:22
 * @author: minphone.linails linails@foxmail.com 
 */

#include "finder.hpp"
#include <iostream>
#include <unistd.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <vector>
#include <typeinfo>

using std::cout;
using std::endl;
using namespace std;

Finder::Finder()
{
}

Finder::~Finder()
{
}


int  Finder::main(int argc, char **argv)
{
    cout << "Finder::main ..." << endl;

    while(1){
        sleep(1);
        this->m_data.clear();

        int ret = this->input(); assert(-1 != ret);

        ret = this->fsort(); assert(-1 != ret);

        ret = this->pairs_forword(); assert(-1 != ret);

        ret = this->output(); assert(-1 != ret);
    }

    return 0;
}

int  Finder::input(void)
{
    cout << "Please input data  | '.' next step !" << endl;

    do{
        int data_in = 0;

        scanf(" %c", (char *)&data_in);

        printf(" data_in : %c \n", data_in);

        if('.' == (char)data_in){
            break;
        }else{
            switch(data_in){
                case '0' ... '9':
                    break;
                case 'a' ... 'z':
                    break;
                case 'A' ... 'Z':
                    break;
                default: break;
            }

            this->m_data.push_back(data_in);
        }

    }while(1);

    return 0;
}

int  Finder::fsort(void)
{
    cout << "fsort() ..." << endl;

    sort(this->m_data.begin(), this->m_data.end(), greater<char>());

    return 0;
}

int  Finder::pairs_forword(void)
{

    list<char>  data_list;

    for(auto data : this->m_data) data_list.push_back(data);

    char forword = '.';

    for(auto iter = data_list.begin(); iter!= data_list.end();){

        if('.' != forword){
            forword = *iter;
        }else{
            if(forword == *iter){
                #if 1
                data_list.push_front(forword);
                iter = data_list.erase(iter);
                #endif
            }else{
                iter++;
            }
        }
    }

    this->m_data_list = data_list;

    return 0;
}

int  Finder::output(void)
{
    for(auto data : this->m_data_list){
        printf("%c , ", data);
    }

    cout << endl;

    return 0;
}



