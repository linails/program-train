/*
 * Progarm Name: other-string.cpp
 * Created Time: 2017-03-14 23:20:43
 * Last modified: 2017-03-15 00:00:41
 * @author: minphone.linails linails@foxmail.com 
 */

#include "other-string.hpp"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

OtherString::OtherString()
{
}

OtherString::~OtherString()
{
}

int  OtherString::main(int argc, char **argv)
{
    int ret = 0;

    {
        string result;

        ret = this->find_reversal(result, "arxbcdefywfedcbz"); assert(-1 != ret);

        if(false == result.empty()){
            cout << "result : " << result << endl;
        }else{
            cout << "find nothing !" << endl;
        }
    }

    return ret;
}

int  OtherString::find_reversal(string &result, const char *str)
{
    if(nullptr != str){
        string ori(str);

        auto pos_first       = ori.begin();
        auto pos_first_r     = ori.rbegin();

        int continue_or_next = -1; // default next

        #if 1
        for(auto iter = ori.begin(); iter != ori.end();){

            if(0 != continue_or_next) iter = pos_first;

            for(auto iter_r = pos_first_r; iter_r != ori.rend(); iter_r++){
                if(0 != continue_or_next){
                    //if((*iter_r == *iter) && (iter != iter_r)){
                    if((*iter_r == *iter)){
                        continue_or_next = 0;
                        pos_first_r++;
                        break;
                    }
                }else{
                    //if((*iter_r == *iter) && (iter != iter_r)){
                    if((*iter_r == *iter)){
                        continue_or_next = 0;
                        pos_first_r++;
                        break;
                    }else{
                        continue_or_next = -1;
                        break;
                    }
                }
            }

            if(0 != continue_or_next){

                if(1< (iter - pos_first)){
                    result = string(++pos_first, iter);
                    break;
                }

                pos_first++;
                pos_first_r = ori.rbegin();
            }else{
                iter++;
            }
        }
        #endif

    }else
        return -1;

    return 0;
}

