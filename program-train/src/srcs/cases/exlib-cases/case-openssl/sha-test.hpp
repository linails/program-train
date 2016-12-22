/*
 * Progarm Name: sha-test.hpp
 * Created Time: 2016-12-15 17:40:21
 * Last modified: 2016-12-22 09:05:01
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SHA_TEST_HPP_
#define _SHA_TEST_HPP_

#include <string>

using std::string;

class shaTest{
public:
    shaTest();
    ~shaTest();
    int  st_main(int argc, char **argv);
private:
    int  str2hex(string &s);
    string sha256(const string &s);
};

#endif //_SHA_TEST_HPP_

