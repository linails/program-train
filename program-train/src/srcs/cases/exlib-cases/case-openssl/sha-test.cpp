/*
 * Progarm Name: sha-test.cpp
 * Created Time: 2016-12-15 17:40:17
 * Last modified: 2016-12-22 12:35:23
 * @author: minphone.linails linails@foxmail.com 
 */

#include "sha-test.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include "openssl/sha.h"

using std::cout;
using std::endl;
using std::string;

shaTest::shaTest()
{
}

shaTest::~shaTest()
{
}

int  shaTest::st_main(int argc, char **argv)
{
    int ret = 0;

    string s("hello world");

    this->str2hex(s);

    cout << "this->sha256() : " << this->sha256(s) << endl;

    ret = this->md5();

    return ret;
}

int  shaTest::str2hex(string &s)
{
    cout << "str2hex ..." << endl;
    int ret = 0;

    cout << "HEX : ";
    for(size_t i=0; i<s.size(); i++){
        printf("%.2x ", s[i]);
    }
    cout << endl;

    return ret;
}

/* 
 * 使用标准的 openssl 库
 * */
string shaTest::sha256(const string &s)
{
    char buf[2];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, s.c_str(), s.size());
    SHA256_Final(hash, &sha256);

    string ns;

    for(int i=0; i<SHA256_DIGEST_LENGTH; i++){
        sprintf(buf, "%.2x", hash[i]);
        ns = ns+buf;
    }

    return ns;
}

int  shaTest::md5(void)
{
    int ret = 0;

    return ret;
}

