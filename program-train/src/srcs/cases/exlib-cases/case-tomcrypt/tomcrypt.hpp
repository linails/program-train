/*
 * Progarm Name: tomcrypt.hpp
 * Created Time: 2017-11-14 16:59:52
 * Last modified: 2017-11-14 17:05:35
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TOMCRYPT_HPP_
#define _TOMCRYPT_HPP_

/* 
 * libtomcrypt 是用 ANSI C标准写成的一个密码库
 * */
class Tomcrypt{
public:
    Tomcrypt();
    ~Tomcrypt();
    int  do_test(void);
private:
};

#endif //_TOMCRYPT_HPP_

