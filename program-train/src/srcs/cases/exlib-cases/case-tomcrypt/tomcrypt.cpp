/*
 * Progarm Name: tomcrypt.cpp
 * Created Time: 2017-11-14 16:59:48
 * Last modified: 2017-11-15 09:47:39
 * @author: minphone.linails linails@foxmail.com 
 */

#include "tomcrypt.hpp"
#include <iostream>
#include "tomcrypt.h"

using std::cout;
using std::endl;

Tomcrypt::Tomcrypt()
{
    cout << "Fn: " << __func__ << endl;
}

Tomcrypt::~Tomcrypt()
{
}

int  Tomcrypt::do_test(void)
{
    int keysize = 20;
    int err;

    if(CRYPT_OK != (err = twofish_keysize(&keysize))){
        printf("[Error] get key size: %s\n", error_to_string(err));
        return -1;
    }else{
        printf("Twofish suggested a key size of %d\n", keysize); // 返回16字节
    }

    return 0;
}

