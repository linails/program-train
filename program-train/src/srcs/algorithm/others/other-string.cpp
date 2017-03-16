/*
 * Progarm Name: other-string.cpp
 * Created Time: 2017-03-14 23:20:43
 * Last modified: 2017-03-16 10:32:18
 * @author: minphone.linails linails@foxmail.com 
 */

#include "other-string.hpp"
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>

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
    cout << "-----------------------------------" << endl;
    {
        char result[1024] = {0, };
        //char ori[] = "arxbcdefywfedcbz";
        char ori[] = "arxbcdfefdcbz";

        cout << "ori = " << ori << endl;
        ret = this->find_reversal(result, ori); assert(-1 != ret);

        if(false == string(result).empty()){
            cout << "result : " << result << endl;
        }else{
            cout << "find nothing !" << endl;
        }
    }
    cout << "-----------------------------------" << endl;

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

int  OtherString::find_reversal(char *result, const char *str)
{
    if(nullptr != str){
        size_t len = strlen(str);

        const char *pos_first       = str;
        const char *pos_first_r     = str + len - 1;

        const char *begin           = str;
        const char *rbegin          = str + len - 1;
        const char *end             = str + len - 1;
        const char *rend            = str;

        int continue_or_next = -1; // default next

        for(const char *iter = begin; iter != end; ){

            if(0 != continue_or_next) iter = pos_first;

            for(const char *iter_r = pos_first_r; iter_r != rend; iter_r--){
                if(0 != continue_or_next){
                    if((*iter_r == *iter) && (iter != iter_r)){
                        continue_or_next = 0;
                        pos_first_r = --iter_r;
                        break;
                    }
                }else{
                    if((*iter_r == *iter) && (iter != iter_r)){
                        continue_or_next = 0;
                        pos_first_r--;
                        break;
                    }else{
                        continue_or_next = -1;
                        break;
                    }
                }
            }

            if(0 != continue_or_next){

                if(1< (iter - pos_first)){
                    memcpy(result, pos_first, iter - pos_first);
                    break;
                }

                pos_first++;
                pos_first_r = rbegin;
            }else{
                iter++;
            }
        }

    }else
        return -1;

    return 0;
}

