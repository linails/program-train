/*
 * Progarm Name: exlibCases.hpp
 * Created Time: 2016-12-21 10:06:04
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _EXLIBCASES_HPP_
#define _EXLIBCASES_HPP_

#define COMPILE_FLAG_exlib_json     0
#define COMPILE_FLAG_exlib_gtest    0
#define COMPILE_FLAG_exlib_xml      0
#define COMPILE_FLAG_exlib_sigslot  1

class exlibCases{
public:
    exlibCases();
    ~exlibCases();
    int  exlibcases_main(int argc, char **argv);
private:
    int  sigslot(void);
};

#endif //_EXLIBCASES_HPP_

