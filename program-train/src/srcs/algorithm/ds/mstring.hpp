/*
 * Progarm Name: mstring.hpp
 * Created Time: 2017-01-07 09:32:37
 * Last modified: 2017-01-07 17:57:53
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MSTRING_HPP_
#define _MSTRING_HPP_

#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using std::cout;
using std::endl;
using std::string;

class mString{
public:
    mString(size_t size = 128);
    mString(const char *str);
    mString(string &s);
    mString(const mString &s);
    ~mString();
    mString operator()(size_t pos, size_t len);
    mString &operator=(const mString &s);
    mString &operator+=(const mString &s);
    mString &operator+=(const char *str);
    mString &operator+=(const string &s);
    int  operator==(const mString &s) const;
    int  operator!=(const mString &s) const;
    int  operator!(void) const;
    char operator[](size_t pos);
    size_t find(const char *pat, int mode = 1) const;
    size_t find(const string &pat, int mode = 1) const;
    size_t length(void) const;
    char *c_str(void) const;
private:
    int  resize(void);
    size_t find_simple(const char *pat) const;
    size_t find_kmp(const char *pat) const;
    int  kmp_getnext(const char *pat, int *next) const;
private:
    size_t  m_size;
    size_t  m_len;
    char   *m_buf;
};

mString::mString(size_t size)
    :m_size(size)
    ,m_len(0)
    ,m_buf(NULL)
{
    this->resize();
}

mString::mString(const char *str)
    :m_buf(NULL)
{
    this->m_len  = strlen(str);
    this->m_size = (this->m_len / 128) + 1;
    this->resize();
    memcpy(this->m_buf, str, this->m_len);
}

mString::mString(string &s)
    :m_buf(NULL)
{
    this->m_len  = s.length();
    this->m_size = (this->m_len / 128) + 1;
    this->resize();
    memcpy(this->m_buf, s.c_str(), this->m_len);
}

mString::mString(const mString &s)
{
    this->m_len  = s.length();
    this->m_size = (this->m_len / 128) + 1;
    this->resize();
    memcpy(this->m_buf, s.c_str(), this->m_len);
}

mString::~mString()
{
    assert(NULL != this->m_buf);

    if(NULL != this->m_buf)
        delete [] this->m_buf;
}

/*
 * 取子串 s = s(3, 4)
 * */
mString mString::operator()(size_t pos, size_t len)
{
    mString ret;

    if(0 < len){
        if(len <= ret.m_size){
            memcpy(ret.m_buf, &(this->m_buf[pos]), len);
        }else{
            ret.resize();
            memcpy(ret.m_buf, &(this->m_buf[pos]), len);
        }
        ret.m_len = len;
    }

    return ret;
}

mString &mString::operator=(const mString &s)
{
    /* 
     *  1. 检查自赋值
     *  2. 释放原有的内存资源
     *  3. 分配新的内存资源，并复制内容
     *  4. 返回本对象的引用
     * */

    if(this == &s){
        cout << "[Error] : this = &s" << endl;
        return *this;
    }

    if(0 < s.length()){
        if(s.length() <= this->m_size){
            memcpy(this->m_buf, s.c_str(), s.length());
        }else{
            this->resize();
            memcpy(this->m_buf, s.c_str(), s.length());
        }
        this->m_len = s.length();
    }else{
        this->m_len = 0;
        memset(this->m_buf, 0, this->m_size);
    }

    return *this;
}

mString &mString::operator+=(const mString &s)
{
    if((this->m_size - this->m_len) > s.length()){
        memcpy(&this->m_buf[this->m_len], s.c_str(), s.length());
    }else{
        this->resize();
        memcpy(&this->m_buf[this->m_len], s.c_str(), s.length());
    }

    this->m_len = this->m_len + s.length();
    return *this;
}

mString &mString::operator+=(const string &s)
{
    if((this->m_size - this->m_len) > s.length()){
        memcpy(&this->m_buf[this->m_len], s.c_str(), s.length());
    }else{
        this->resize();
        memcpy(&this->m_buf[this->m_len], s.c_str(), s.length());
    }

    this->m_len = this->m_len + s.length();
    return *this;
}

mString &mString::operator+=(const char *str)
{
    size_t len = strlen(str);
    if((this->m_size - this->m_len) > len){
        memcpy(&this->m_buf[this->m_len], str, len);
    }else{
        this->resize();
        memcpy(&this->m_buf[this->m_len], str, len);
    }

    this->m_len = this->m_len + len;
    return *this;
}

int  mString::operator==(const mString &s) const
{
    bool ret = true;

    if(this->m_len == s.length()){
        for(size_t i=0; i<this->m_len; i++){
            if(this->m_buf[i] != s.m_buf[i]){
                ret = false;
                break;
            }
        }
    }else
        ret = false;

    return ret;
}

int  mString::operator!=(const mString &s) const
{
    bool ret = false;

    if(this->m_len == s.length()){
        for(size_t i=0; i<this->m_len; i++){
            if(this->m_buf[i] != s.m_buf[i]){
                ret = true;
                break;
            }
        }
    }else
        ret = true;

    return ret;
}

int  mString::operator!(void) const
{
    bool ret = true;

    if(0 != this->m_len) ret = false;

    return ret;
}

size_t mString::length(void) const
{
    return this->m_len;
}

char mString::operator[](size_t pos)
{
    char ret = 0x00;

    if(pos <= this->m_len - 1) ret = this->m_buf[pos];

    return ret;
}

/* 
 * mode = 0 : simple default
 * mode = 1 : KMP
 *
 * return   : index , faile = -1
 * */
size_t mString::find(const char *pat, int mode) const
{
    size_t ret = -1;

    switch(mode){
        case 0 : ret = this->find_simple(pat);  break;
        case 1 : ret = this->find_kmp(pat);     break;
        default: ret = -1;                      break;
    }

    return ret;
}

size_t mString::find(const string &pat, int mode) const
{
    return this->find(pat.c_str(), mode);
}

size_t mString::find_simple(const char *pat) const
{
    size_t ret = -1;
    size_t len = strlen(pat);

    for(size_t i=0, j=0; i<this->m_len; i++){
        for(; j<len; j++){
            if(this->m_buf[i + j] != pat[j]) break;
        }
        if(j-1 == len){
            ret = i;
            break;
        }
    }

    return ret;
}

/* 
 * KMP
 * */
size_t mString::find_kmp(const char *pat) const
{
    int next[128] = {0, };

    this->kmp_getnext(pat, next);

    size_t len = strlen(pat);

    cout << "next : ";
    for(size_t i=0; i<len; i++){
        cout << next[i] << " ";
    }
    cout << endl;

    return 0;
}

/*
 * 理解KMP算法的关键：
 *
 *  1> next[i] = j; 这条语句是说，在顺次比较中，主串已经比较到了第 i-1 个字符，子串已经比较到了第
 *     j-1 个字符，而前面的这 j-1 个字符都是相等的，下面比较主串中的第 i 个字符与子串中的第 j 个
 *     字符，当他们不等时，i 指针不用回溯，j 指针需要回溯，j 指针回溯的位置即为 next[j]。总之，用
 *     一句话概括就是，当子串匹配到第 i 个字符和主串不相等时，主串不用回溯，子串需要回溯到 j 的位置
 *
 *  2> j = next[j]; 这句语句是子串回溯时跳转的动作，子串从位置 j 回溯到位置 next[j]
 *
 *              / -1    , 当 j = 0
 *  3> next(j) =  k+1   , 当 0 <= k < j-1 且使得 P0P1 ... Pk = Pj-k-1Pj-k...Pj-1 的最大整数
 *              \  0    , 其他情况
 *
 *      j   |    0    1    2    3    4    5    6    7
 *  --------+---------------------------------------------
 *      P   |    a    b    a    a    b    c    a    c
 *   next(j)|   -1    0    0    1    1    2    0    1
 *
 * */
int  mString::kmp_getnext(const char *pat, int *next) const
{
    int k = -1;

    size_t j = 0;
    size_t pat_len = strlen(pat);

    next[0] = -1;

    while(j < pat_len){
        if(-1 == k || pat[j] == pat[k]){
            j++;
            k++;
            next[j] = k;
        }else
            k = next[k];
    }

    return 0;
}

char *mString::c_str(void) const
{
    return this->m_buf;
}

int  mString::resize(void)
{
    if(NULL == this->m_buf){
        this->m_buf = new char[this->m_size];
        if(NULL == this->m_buf){
            cout << "[Error] : new char[size] failed" << endl;
            exit(1);
        }
        memset(this->m_buf, 0, this->m_size);
    }else{
        char *buf = new char[this->m_size * 2];

        memcpy(buf, this->m_buf, this->m_size);

        delete [] this->m_buf;

        this->m_buf  = buf;
        this->m_size = this->m_size * 2;
    }

    return 0;
}

#endif //_MSTRING_HPP_

